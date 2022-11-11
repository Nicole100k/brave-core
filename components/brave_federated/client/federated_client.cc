/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_federated/client/federated_client.h"

#include <list>
#include <map>
#include <sstream>
#include <tuple>

#include "base/check.h"
#include "base/task/sequenced_task_runner.h"
#include "base/task/thread_pool.h"
#include "base/threading/sequence_bound.h"
#include "base/threading/sequenced_task_runner_handle.h"

#include "brave/components/brave_federated/client/communication_helper.h"
#include "brave/components/brave_federated/client/model.h"

#include "brave/third_party/flower/src/cc/flwr/include/typing.h"

#include "net/http/http_request_headers.h"
#include "net/traffic_annotation/network_traffic_annotation.h"
#include "services/network/public/cpp/resource_request.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "services/network/public/cpp/simple_url_loader.h"

namespace brave_federated {

namespace {

constexpr char kServerEndpoint[] = "https://fl.brave.com";

// TODO(lminto): update this annotation
net::NetworkTrafficAnnotationTag GetNetworkTrafficAnnotationTag() {
  return net::DefineNetworkTrafficAnnotation("federated_learning", R"(
        semantics {
          sender: "Federated Learning"
          description:
            "Report of anonymized engagement statistics. For more info see "
          trigger:
            "Reports are automatically generated on startup and at intervals "
            "while Brave is running."
          data:
            "Anonymized and encrypted engagement data."
          destination: WEBSITE
        }
        policy {
          cookies_allowed: NO
          setting:
            "This service is enabled only when opted in to ads and having "
            "P3A is enabled."
          policy_exception_justification:
            "Not implemented."
        }
    )");
}
}

FederatedClient::FederatedClient(
    const std::string& task_name,
    Model* model,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory)
    : url_loader_factory_(url_loader_factory),
      task_name_(task_name),
      model_(model) {
  DCHECK(model_);
  DCHECK(url_loader_factory_);
}

FederatedClient::~FederatedClient() {
  Stop();
}

void FederatedClient::Start() {
  GetTasks();
}

void FederatedClient::Stop() {
  DCHECK(is_communicating_);
  is_communicating_ = false;
}

void FederatedClient::GetTasks() {
  auto request = std::make_unique<network::ResourceRequest>();
  request->url = GURL(kServerEndpoint);
  request->headers.SetHeader("X-Brave-FL-Federated-Learning", "?1");
  request->credentials_mode = network::mojom::CredentialsMode::kOmit;
  request->method = net::HttpRequestHeaders::kGetMethod;

  VLOG(2) << "Requesting Tasks list " << request->method << " " << request->url;

  const std::string payload = BuildGetTasksPayload();

  VLOG(2) << "Payload " << payload;

  url_loader_ = network::SimpleURLLoader::Create(
      std::move(request), GetNetworkTrafficAnnotationTag());
  url_loader_->AttachStringForUpload(payload, "application/json");
  url_loader_->DownloadHeadersOnly(
      url_loader_factory_.get(),
      base::BindOnce(&FederatedClient::OnGetTasks, base::Unretained(this)));
}

void FederatedClient::OnGetTasks(
    scoped_refptr<net::HttpResponseHeaders> headers) {
  if (!headers) {
    VLOG(1) << "Failed to get federated tasks";
    return;
  }
}

void FederatedClient::PostTaskResults() {
  auto request = std::make_unique<network::ResourceRequest>();
  request->url = GURL(kServerEndpoint);
  request->headers.SetHeader("X-Brave-FL-Federated-Learning", "?1");
  request->credentials_mode = network::mojom::CredentialsMode::kOmit;
  request->method = net::HttpRequestHeaders::kPostMethod;

  VLOG(2) << "Posting Task results " << request->method << " " << request->url;

  const std::string payload = BuildPostTaskResultsPayload();

  VLOG(2) << "Payload " << payload;

  url_loader_ = network::SimpleURLLoader::Create(
      std::move(request), GetNetworkTrafficAnnotationTag());
  url_loader_->AttachStringForUpload(payload, "application/json");
  url_loader_->DownloadHeadersOnly(
      url_loader_factory_.get(),
      base::BindOnce(&FederatedClient::OnPostTaskResults,
                     base::Unretained(this)));
}

void FederatedClient::OnPostTaskResults(
    scoped_refptr<net::HttpResponseHeaders> headers) {
  if (!headers) {
    VLOG(1) << "Failed to post task results";
    return;
  }
}

bool FederatedClient::IsCommunicating() {
  return is_communicating_;
}

Model* FederatedClient::GetModel() {
  return model_;
}

void FederatedClient::SetTrainingData(
    DataSet training_data) {
  training_data_ = training_data;
}

void FederatedClient::SetTestData(DataSet test_data) {
  test_data_ = test_data;
}

// flwr::ParametersRes FederatedClient::GetParameters() {
//   // Serialize
//   const Weights prediction_weights = model_->GetPredWeights();
//   const float prediction_bias = model_->Bias();

//   std::list<std::string> tensors;

//   std::ostringstream oss1;
//   oss1.write(reinterpret_cast<const char*>(prediction_weights.data()),
//              prediction_weights.size() * sizeof(float));
//   tensors.push_back(oss1.str());

//   std::ostringstream oss2;
//   oss2.write(reinterpret_cast<const char*>(&prediction_bias), sizeof(float));
//   tensors.push_back(oss2.str());

//   std::string tensor_string = "cpp_float";
//   return flwr::ParametersRes(flwr::Parameters(tensors, tensor_string));
// }

// const float* GetLayerWeightsFromString(std::string layer_string) {
//   const char* weights_char = (layer_string).c_str();
//   return reinterpret_cast<const float*>(weights_char);
// }

// void FederatedClient::SetParameters(flwr::Parameters parameters) {
//   std::list<std::string> tensor_string = parameters.getTensors();

//   if (tensor_string.empty() == 0) {
//     // Layer 1
//     auto layer = tensor_string.begin();
//     size_t num_bytes = (*layer).size();
//     auto* weights_float = GetLayerWeightsFromString(*layer);
//     Weights weights(weights_float,
//                     weights_float + num_bytes / sizeof(float));
//     model_->SetPredWeights(weights);

//     // Layer 2 = Bias
//     auto* bias_float = GetLayerWeightsFromString(*std::next(layer, 1));
//     model_->SetBias(bias_float[0]);
//   }
// }
// flwr::PropertiesRes FederatedClient::GetProperties(flwr::PropertiesIns
// instructions) {
//   flwr::PropertiesRes properties;
//   properties.setPropertiesRes(static_cast<flwr::Properties>(instructions.getPropertiesIns()));
//   return properties;
// }

// flwr::FitRes FederatedClient::Fit(flwr::FitIns instructions) {
//   auto config = instructions.getConfig();
//   flwr::FitRes response;
//   flwr::Parameters parameters = instructions.getParameters();
//   SetParameters(parameters);

//   std::tuple<size_t, float, float> result =
//       model_->Train(training_data_);

//   response.setParameters(GetParameters().getParameters());
//   response.setNum_example(std::get<0>(result));

//   return response;
// }

// flwr::EvaluateRes FederatedClient::Evaluate(flwr::EvaluateIns instructions) {
//   flwr::EvaluateRes response;
//   flwr::Parameters parameters = instructions.getParameters();
//   SetParameters(parameters);

//   // Evaluation returns a number_of_examples, a loss and an "accuracy"
//   std::tuple<size_t, float, float> result =
//       model_->Evaluate(test_data_);

//   response.setNum_example(std::get<0>(result));
//   response.setLoss(std::get<1>(result));

//   flwr::Scalar accuracy = flwr::Scalar();
//   accuracy.setDouble(static_cast<double>(std::get<2>(result)));
//   std::map<std::string, flwr::Scalar> metric = {
//       {"accuracy", accuracy},
//   };
//   response.setMetrics(metric);
//   return response;
// }

}  // namespace brave_federated
