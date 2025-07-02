import litgen
import litgen.options
import os
from functools import partial

##################
# helper functions
##################
def wrap_pybind11_module(module_name: str, code: str) -> str:
    prefix = f"""
#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "{module_name}.hpp"
PYBIND11_MODULE({module_name}, m) {'{'}
"""
    suffix = "}\n"
    return prefix + code + suffix

def generated_file_name(out_dir, name, ext):
    os.makedirs(output_dir, exist_ok=True)
    return f"{out_dir}/{name.replace('.hpp', f'_bindings.{ext}')}"

###########################
# main code
###########################
headers = [
    "pose_module.hpp"
]

output_dir = "generated"

for header in headers:
    options = litgen.LitgenOptions()
    options.postprocess_pydef_function = lambda code: wrap_pybind11_module(header.replace(".hpp", ""), code)
    generated_code = litgen.generate_code_for_file(options, header)

    if generated_code.pydef_code:
        with open(generated_file_name(output_dir, header, "cpp"), "w") as bindings_file:
            bindings_file.write(generated_code.pydef_code)

    if generated_code.stub_code:
        with open(generated_file_name(output_dir, header, "pyi"), "w") as stub_file:
            stub_file.write(generated_code.stub_code)

