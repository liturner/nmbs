//
// Created by luke on 6/6/26.
//

#ifndef TT_NMBS_NMBS_H
#define TT_NMBS_NMBS_H

#include <string>

namespace nmbs
{
    std::string nmbs_confidentiality_label(const std::string& policyIdentifier, const std::string& classification);

    std::string canonicalize(const std::string& text);
}

#endif //TT_NMBS_NMBS_H
