/// @file test.h
/// @brief The single "include all" header for testing units.
///
/// @author Luke Ian Turner
/// @date 2026-06-26
/// @copyright Copyright (c) 2026 Luke Ian Turner
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// @copyright
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#pragma once

#include <gtest/gtest.h>
#include <random>

#include "nmbs/nmbs.h"
#include "nmbs/nmbs_private.h"

#include "nmbs/nmbs_c.h"

namespace nmbs::test
{
    class RootRelevantTest : public ::testing::Test {
    protected:
        static bool running_as_root() {
            return geteuid() == 0;
        }
    };

    class IsolatedResourcesTest : public ::testing::Test {
    protected:
        std::filesystem::path temp_test_dir_;
        std::filesystem::path source_resources_dir_ = std::filesystem::absolute("resources");

        void SetUp() override {
            ASSERT_TRUE(std::filesystem::exists(source_resources_dir_))
                << "Source resources folder not found at: " << source_resources_dir_;

            const std::filesystem::path temp_base = std::filesystem::temp_directory_path();

            // Generate a random unique folder name to prevent parallel test collisions
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<uint64_t> dis;
            const std::string unique_dir_name = "test_resources_" + std::to_string(dis(gen));
            temp_test_dir_ = temp_base / unique_dir_name;
            std::filesystem::create_directories(temp_test_dir_);

            std::filesystem::copy(source_resources_dir_, temp_test_dir_ / "resources", std::filesystem::copy_options::recursive);
        }

        void TearDown() override {
            if (std::filesystem::exists(temp_test_dir_)) {
                std::filesystem::remove_all(temp_test_dir_);
            }
        }

        // Helper function so your individual tests can easily find the copied files
        [[nodiscard]] std::filesystem::path get_temp_resources_dir() const {
            return temp_test_dir_ / "resources";
        }
    };

}
