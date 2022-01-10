#include "clove.h"
#include "test_filler_algo.h"
#include "test_filler.h"

CLOVE_RUNNER(FillerAlgo_OnePixelWithSuccess, FillerAlgo_OnePixelWithSameColor,FillerAlgo_OnePixelOutOfRange,
            FillerAlgo_IncorrectNumberOfChannels, FillerAlgo_1x3First2PixelsUpdated, Filler_RedSquare16x16);