/*
 *  Copyright 2017 Adam Dicker
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <stdalign.h>
#include <stdint.h>

#include "block-tests.h"
#include "br_if-tests.h"
#include "br_table-tests.h"
#include "call-tests.h"
#include "const-tests.h"
#include "f32-tests.h"
#include "f64-tests.h"
#include "i32-tests.h"
#include "i64-tests.h"
#include "if-tests.h"
#include "loop-tests.h"
#include "memory-tests.h"
#include "nop-tests.h"
#include "return-tests.h"
#include "test-common.h"

#define MAX_FILE_PATH 4096

void print_header()
{
    printf("--------------------------------------------------------------------------------\n");
    printf("                                                                                \n");
    printf("                             WARP SPEC TESTS                                    \n");
    printf("                                                                                \n");
    printf("--------------------------------------------------------------------------------\n");
}

void print_footer(uint32_t passed, uint32_t failed)
{
    printf(GREEN_TEXT("passed:%d  "), passed);
    printf(RED_TEXT("failed:%d\n\n"), failed);

    if (failed == 0) {
        printf(GREEN_TEXT("spec tests passed"));
    } else {
        printf(RED_TEXT("spec tests failed"));
    }
}

int main(int argc, char **argv)
{
    ASSERT(argc >= 2, "invalid args");

    print_header();

    wrp_vm_t *vm = wrp_open_vm(test_alloc, test_free);
    ASSERT(vm, "vm failed to initialise");

    uint8_t *path_buf = test_alloc(MAX_FILE_PATH + 1, alignof(uint8_t));
    ASSERT(path_buf, "failed to allocate path buffer");

    uint32_t passed = 0;
    uint32_t failed = 0;
    run_block_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_br_if_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_br_table_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_call_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_const_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_f32_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_f64_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_i32_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_i64_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_if_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_loop_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_memory_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_nop_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);
    run_return_tests(vm, argv[1], path_buf, MAX_FILE_PATH + 1, &passed, &failed);

    test_free(path_buf);
    wrp_close_vm(vm);

    print_footer(passed, failed);

    return (failed == 0) ? 0 : 1;
}
