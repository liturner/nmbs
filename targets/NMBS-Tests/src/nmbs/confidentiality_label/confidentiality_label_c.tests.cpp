/// @file confidentiality_label_c.cpp
/// @brief confidentiality_label_c.cpp brief
/// @details confidentiality_label_c.cpp details
///
/// @author luke
/// @date 2026-07-22
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

TEST(ConfidentialityLabelC, ReadWriteOriginatorId)
{
    const std::string a = nmbs::ConfidentialityLabel::OriginatorId::rfc822_name;
    const std::string b = "Test@Name";
    const std::string c = "Something";
    const std::string d = "Another Something";

    nmbs::ConfidentialityLabel label;
    auto c_label = reinterpret_cast<nmbs_confidentiality_label_ptr>(&label);
    ASSERT_FALSE(nmbs_confidentiality_label_get_originator_id_type(c_label));
    ASSERT_FALSE(nmbs_confidentiality_label_get_originator_id(c_label));

    label.originator_id = nmbs::ConfidentialityLabel::OriginatorId{
        a,
        b};
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id_type(c_label), a.c_str());
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id(c_label), b.c_str());
    ASSERT_EQ(label.originator_id->id_type, a);
    ASSERT_EQ(label.originator_id->value, b);

    ASSERT_NE(nmbs_confidentiality_label_set_originator_id(c_label, nullptr, nullptr), nmbs::success);
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id_type(c_label), a.c_str());
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id(c_label), b.c_str());
    ASSERT_EQ(label.originator_id->id_type, a);
    ASSERT_EQ(label.originator_id->value, b);

    ASSERT_NE(nmbs_confidentiality_label_set_originator_id(c_label, c.c_str(), nullptr), nmbs::success);
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id_type(c_label), a.c_str());
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id(c_label), b.c_str());
    ASSERT_EQ(label.originator_id->id_type, a);
    ASSERT_EQ(label.originator_id->value, b);

    ASSERT_NE(nmbs_confidentiality_label_set_originator_id(c_label, nullptr, c.c_str()), nmbs::success);
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id_type(c_label), a.c_str());
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id(c_label), b.c_str());
    ASSERT_EQ(label.originator_id->id_type, a);
    ASSERT_EQ(label.originator_id->value, b);

    ASSERT_NE(nmbs_confidentiality_label_set_originator_id(nullptr, c.c_str(), d.c_str()), nmbs::success);
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id_type(c_label), a.c_str());
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id(c_label), b.c_str());
    ASSERT_EQ(label.originator_id->id_type, a);
    ASSERT_EQ(label.originator_id->value, b);

    ASSERT_EQ(nmbs_confidentiality_label_set_originator_id(c_label, c.c_str(), d.c_str()), nmbs::success);
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id_type(c_label), c.c_str());
    ASSERT_STREQ(nmbs_confidentiality_label_get_originator_id(c_label), d.c_str());
    ASSERT_EQ(label.originator_id->id_type, c);
    ASSERT_EQ(label.originator_id->value, d);
}
