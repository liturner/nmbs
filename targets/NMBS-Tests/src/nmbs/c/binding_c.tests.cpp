/// @file binding_c.tests.cpp
/// @brief Tests for the C API
///
/// @author Luke Ian Turner
/// @date 2026-08-01
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

class CBindingInformation : public nmbs::test::IsolatedResourcesTest {

};

TEST_F(CBindingInformation, NewDeleteBindingInformation)
{
    auto binding = nmbs_binding_information_new();
    ASSERT_NE(binding, nullptr);
    nmbs_binding_information_delete(binding);
    ASSERT_NE(binding, nullptr);
}

TEST_F(CBindingInformation, ReadXmpBinding)
{
    const auto test_file_xmp = get_temp_resources_dir() / "test-public-unmarked.jpg";
    const auto test_file_sidecar = get_temp_resources_dir() / "xml/test.1";

    auto binding = nmbs_binding_information_new();
    ASSERT_NE(binding, nullptr);
    nmbs_binding_information_read(binding, test_file_xmp.c_str());
    auto binding_profile = nmbs_binding_information_get_binding_profile(binding);
    ASSERT_STREQ(binding_profile, std::string(nmbs::binding::xmp::profile_version_identifier).c_str());

    nmbs_binding_information_read(binding, test_file_sidecar.c_str());
    binding_profile = nmbs_binding_information_get_binding_profile(binding);
    ASSERT_STREQ(binding_profile, std::string(nmbs::binding::sidecar::profile_version_identifier).c_str());

    nmbs_binding_information_delete(binding);
    nmbs::cleanup();
}
