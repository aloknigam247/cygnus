/************************************************************************************
 * MIT License                                                                      *
 *                                                                                  *
 * Copyright (c) 2020 Alok Nigam                                                    *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy     *
 * of this software and associated documentation files (the "Software"), to deal    *
 * in the Software without restriction, including without limitation the rights     *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 * copies of the Software, and to permit persons to whom the Software is            *
 * furnished to do so, subject to the following conditions:                         *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in all   *
 * copies or substantial portions of the Software.                                  *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    *
 * SOFTWARE.                                                                        *
 ************************************************************************************/

#include "options.h"
#include "cycompile.h"
#include "log.h"
#include "utils.h"
#include "clg.h"

int main(const int argc, const char* argv[]) {
    Options opt;
    opt.addOption("-v", Option::BOOL, "version");
    if(!opt.parse(argc, argv))
        return 1;

    if(opt.isSet("-v"))
        std::cout << "Cygnus " << MAKE_STRING(VERSION) << '\n';

    const std::vector<std::string> &pos = opt.get_positional();

    if(pos.empty())
        return 0;

    Log::i("File: ", pos.front());

    CyCompile compile(pos.front());

    CLG clg(pos.front());
    return 0;
}
