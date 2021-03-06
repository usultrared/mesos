/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <process/future.hpp>
#include <process/gtest.hpp>
#include <process/http.hpp>
#include <process/pid.hpp>

#include "master/master.hpp"

#include "tests/mesos.hpp"
#include "tests/utils.hpp"


using mesos::internal::master::Master;

using process::Future;
using process::PID;

using process::http::BadRequest;
using process::http::Response;

namespace mesos {
namespace internal {
namespace tests {


class HttpApiTest : public MesosTest {};


// TODO(anand): Add additional tests for validation.
TEST_F(HttpApiTest, NoContentType)
{
  Try<PID<Master>> master = StartMaster();
  ASSERT_SOME(master);

  // Expect a BadRequest when 'Content-Type' is omitted.
  //
  // TODO(anand): Send a valid call here to ensure that
  // the BadRequest is only due to the missing header.
  Future<Response> response = process::http::post(
      master.get(),
      "call",
      None(),
      None());

  AWAIT_EXPECT_RESPONSE_STATUS_EQ(BadRequest().status, response);
}

} // namespace tests {
} // namespace internal {
} // namespace mesos {
