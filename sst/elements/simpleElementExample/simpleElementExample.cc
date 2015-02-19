// Copyright 2009-2014 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2014, Sandia Corporation
// All rights reserved.
// 
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#include "sst_config.h"
#include "sst/core/element.h"

#include "simpleComponent.h"
#include "simpleClockerComponent.h"
#include "simpleDistribComponent.h"
#include "simpleRNGComponent.h"
#include "simpleStatisticsComponent.h"
#include "simpleTracerComponent.h"

using namespace SST;
using namespace SST::SimpleComponent;
using namespace SST::SimpleClockerComponent;
using namespace SST::SimpleDistribComponent;
using namespace SST::SimpleRNGComponent;
using namespace SST::SimpleStatisticsComponent;
using namespace SST::SimpleTracerComponent;

static Component* create_simpleComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleComponent( id, params );
}

static Component* create_simpleClockerComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleClockerComponent( id, params );
}

static Component* create_simpleDistribComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleDistribComponent( id, params );
}

static Component* create_simpleRNGComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleRNGComponent( id, params );
}

static Component* create_simpleStatisticsComponent(SST::ComponentId_t id, SST::Params& params)
{
    return new simpleStatisticsComponent(id, params);
}

static Component* create_simpleTracerComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleTracerComponent(id, params);
};


static const ElementInfoParam simpleComponent_params[] = {
    { "workPerCycle", "Count of busy work to do during a clock tick.", NULL},
    { "commFreq", "Approximate frequency of sending an event during a clock tick.", NULL},
    { "commSize", "Size of communication to send.", "16"},
    { NULL, NULL, NULL}
};

static const ElementInfoParam simpleClockerComponent_params[] = {
    { "clock", "Clock frequency", "1GHz" },
    { "clockcount", "Number of clock ticks to execute", "100000"},
    { NULL, NULL, NULL }
};

static const ElementInfoParam simpleDistribComponent_params[] = {
	{ "count", "Number of random values to generate from the distribution", "1000"},
	{ "distrib", "Random distribution to use - \"gaussian\" (or \"normal\"), or \"exponential\"", "gaussian"},
	{ "mean", "Mean value to use if we are sampling from the Gaussian/Normal distribution", "1.0"},
	{ "stddev", "Standard deviation to use for the distribution", "0.2"},
	{ "lambda", "Lambda value to use for the exponential distribution", "1.0"},
	{ "binresults", "Print the results, only if value is \"1\"", "1"},
  	{ NULL, NULL, NULL }
};

static const ElementInfoParam simpleRNGComponent_params[] = {
    { "seed_w", "The seed to use for the random number generator", "7" },
    { "seed_z", "The seed to use for the random number generator", "5" },
    { "seed", "The seed to use for the random number generator.", "11" },
    { "rng", "The random number generator to use (Marsaglia or Mersenne), default is Mersenne", "Mersenne"},
    { "count", "The number of random numbers to generate, default is 1000", "1000" },
    { NULL, NULL }
};

static const ElementInfoParam simpleStatisticsComponent_params[] = {
    { "seed_w", "The seed to use for the random number generator", "7" },
    { "seed_z", "The seed to use for the random number generator", "5" },
    { "seed", "The seed to use for the random number generator.", "11" },
    { "rng", "The random number generator to use (Marsaglia or Mersenne), default is Mersenne", "Mersenne"},
    { "count", "The number of random numbers to generate, default is 1000", "1000" },
    { NULL, NULL }
};

static const ElementInfoParam simpleTracerComponent_params[] = {
    {"clock", "Frequency, same as system clock frequency", "1 Ghz"},
    {"statsPrefix", "writes stats to statsPrefix file", ""},
    {"tracePrefix", "writes trace to tracePrefix tracing is enable", ""},
    {"debug", "Print debug statements with increasing verbosity [0-10]", "0"},
    {"statistics", "0-No-stats, 1-print-stats", "0"},
    {"pageSize", "Page Size (bytes), used for selecting number of bins for address histogram ", "4096"},
    {"accessLatencyBins", "Number of bins for access latency histogram" "10"},
    {NULL, NULL}
};

static const ElementInfoStatisticEnable simpleStatisticsComponent_statistics[] = {
    { "histo_U32", "Test Histogram 1 - Collecting U32 Data", 1},   // Name, Desc, Enable Level 
    { "histo_U64", "Test Histogram 2 - Collecting U64 Data", 2}, 
    { "histo_I32", "Test Histogram 3 - Collecting IU32 Data", 3}, 
    { "histo_I64", "Test Histogram 4 - Collecting I64 Data", 4},     
    { "accum_U32", "Test Accumulator 1 - Collecting U32 Data", 5}, 
    { "accum_U64", "Test Accumulator 1 - Collecting U64 Data", 6}, 
    { NULL, NULL, 0 }
};

static const char* simpleComponent_port_events[] = { "simpleComponent.simpleComponentEvent", NULL };

static const ElementInfoPort simpleComponent_ports[] = {
    {"Nlink", "Link to the simpleComponent to the North", simpleComponent_port_events},
    {"Slink", "Link to the simpleComponent to the South", simpleComponent_port_events},
    {"Elink", "Link to the simpleComponent to the East",  simpleComponent_port_events},
    {"Wlink", "Link to the simpleComponent to the West",  simpleComponent_port_events},
    {NULL, NULL, NULL}
};

const char* simpleTracerComponent_memEvent_List[] = {"MemEvent", NULL};

static const ElementInfoPort simpleTracerComponent_ports[] = {
    {"northBus", "Connect towards cpu side", simpleTracerComponent_memEvent_List},
    {"southBus", "Connect towards memory side", simpleTracerComponent_memEvent_List},
    {NULL, NULL, NULL}
};


static const ElementInfoComponent simpleElementComponents[] = {
    { "simpleComponent",                                 // Name
      "Simple Demo Component",                           // Description
      NULL,                                              // PrintHelp
      create_simpleComponent,                            // Allocator
      simpleComponent_params,                            // Parameters
      simpleComponent_ports,                             // Ports
      COMPONENT_CATEGORY_PROCESSOR,                      // Category
      NULL                                               // Statistics
    },
    { "simpleClockerComponent",                          // Name
      "Clock Benchmark Component",                       // Description
      NULL,                                              // PrintHelp
      create_simpleClockerComponent,                     // Allocator
      simpleClockerComponent_params,                     // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    { "simpleDistribComponent",                          // Name
      "Random Number Distribution Component",            // Description
      NULL,                                              // PrintHelp
      create_simpleDistribComponent,                     // Allocator
      simpleDistribComponent_params,                     // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    { "simpleRNGComponent",                              // Name
      "Random number generation component",              // Description
      NULL,                                              // PrintHelp
      create_simpleRNGComponent,                         // Allocator
      simpleRNGComponent_params,                         // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    { "simpleStatisticsComponent",                       // Name
      "Statistics Demo Component",                       // Description
      NULL,                                              // PrintHelp
      create_simpleStatisticsComponent,                  // Allocator
      simpleStatisticsComponent_params,                  // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      simpleStatisticsComponent_statistics               // Statistics
    },
    { "simpleTracerComponent",                           // Name
      "Simple Tracer And Stats Collector Component",     // Description
      NULL,                                              // PrintHelp
      create_simpleTracerComponent,                      // Allocator
      simpleTracerComponent_params,                      // Parameters
      simpleTracerComponent_ports,                       // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL}
};

extern "C" {
    ElementLibraryInfo simpleElementExample_eli = {
        "simpleElementExample",                          // Name
        "A Simple Example Element With Demo Components", // Description
        simpleElementComponents,                         // Components
        NULL,                                            // Events 
        NULL,                                            // Introspectors 
        NULL,                                            // Modules 
        NULL,                                            // Subcomponents 
        NULL,                                            // Partitioners
        NULL,                                            // Python Module Generator
        NULL                                             // Generators
    };
}


