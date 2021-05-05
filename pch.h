// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <cmath>

#include <aced.h>
#include <accmd-defs.h>
#include <accmd.h>
#include <rxregsvc.h>

#include "acutads.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "gearc3d.h"
#include "dbelipse.h"
#include "dbspline.h"

#include <map>
#include <string>
#include <tuple>

#include "Helpers.h"
DECLARE_CMDS_LIST;

#endif //PCH_H
