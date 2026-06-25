#pragma once

#include <gtest/gtest.h>

#include "nmbs/nmbs.h"
#include "nmbs/binding.h"
#include "nmbs/constants.h"
#include "nmbs_private.h"

#define NMBS_REQUIREMENT_SOURCE(SOURCE) RecordProperty("requirement_source", #SOURCE);
#define NMBS_REQUIREMENT_TEXT(REQUIREMENT) RecordProperty("requirement_text", #REQUIREMENT);

#define NMBS_REQUIREMENT_STANDARD_4778_2_A1 NMBS_REQUIREMENT_SOURCE(ADatP-4778.2 Ed.A V.1)
