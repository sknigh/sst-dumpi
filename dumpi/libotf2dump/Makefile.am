#
#   This file is part of DUMPI: 
#                The MPI profiling library from the SST suite.
#   Copyright (c) 2009 Sandia Corporation.
#   This software is distributed under the BSD License.
#   Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
#   the U.S. Government retains certain rights in this software.
#   For more information, see the LICENSE file in the top 
#   SST/macroscale directory.
#

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)
AM_LDFLAGS =
library_includedir=$(includedir)/dumpi/libotf2dump
library_include_HEADERS = \
                      otf2writer.h otf2writer-defs.h
lib_LTLIBRARIES = libotf2dump.la

libotf2dump_la_SOURCES = \
                      otf2writer.cc \
                      otf2deftable.cc \
                      rankcontext.cc \
                      commsplitconstructor.cc \
                      commcreateconstructor.cc

libotf2dump_la_LDFLAGS = -version-info @DUMPI_LIBVERSION@
libotf2dump_la_LIBADD = ../common/libdumpi_common.la
