/// @file remove_binding.tests.cpp
/// @brief remove_binding.tests.cpp brief
/// @details remove_binding.tests.cpp details
///
/// @author Luke Ian Turner
/// @date 2026-07-31
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

#include <nmbs/test.h>

class RemoveBinding : public nmbs::test::IsolatedResourcesTest {

};

TEST_F(RemoveBinding, Xmp)
{
    const auto test_file = get_temp_resources_dir() / "test-has-label.jpg";
    ASSERT_TRUE(std::filesystem::exists(test_file))
                << "test-has-label.jpg resource not found at: " << get_temp_resources_dir();

    const auto result = nmbs::remove_binding(test_file);
    ASSERT_TRUE(result.has_value());

    const auto no_labels = nmbs::read_binding(test_file);
    ASSERT_FALSE(no_labels.value().has_value()) << "Removing the binding seems to have failed.";
}

TEST_F(RemoveBinding, Sidecar)
{
    const auto test_file = get_temp_resources_dir() / "xml/test.1";

    const auto has_labels = nmbs::read_binding(test_file);
    ASSERT_EQ(has_labels.value().value().labels.size(), 1) << "Test file should have had a binding to start with?";

    const auto result = nmbs::remove_binding(test_file);
    ASSERT_TRUE(result.has_value());

    const auto no_labels = nmbs::read_binding(test_file);
    ASSERT_FALSE(no_labels.value().has_value()) << "Removing the binding seems to have failed.";
}
