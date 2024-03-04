#include <iostream>
#include <vector>

#include "utils/Vector.hpp"
#include "utils/LinAlg.hpp"
#include "utils/coordinates.hpp"
#include "utils/file_input/ParametersInputter.hpp"
#include "utils/file_input/filenames.hpp"

#include "global/GlobalScope.hpp"
#include "global/Constants.hpp"

#include "core/Core.hpp"

int main() {
    Core core;

    auto result = core.calculateEndpoint();

    std::cout << "\nFinished.\n";

    return 0;
}