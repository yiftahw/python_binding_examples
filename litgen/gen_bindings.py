import litgen

headers = [
    "pose.hpp"
]

output_dir = "generated"

for header in headers:
    options = litgen.LitgenOptions()
    generated_code = litgen.generate_code_for_file(options, header)

    if generated_code.pydef_code:
        with open(header.replace(".hpp", "_bindings.hpp"), "w") as bindings_file:
            bindings_file.write(generated_code.pydef_code)

    if generated_code.stub_code:
        with open(header.replace(".hpp", ".pyi"), "w") as stub_file:
            stub_file.write(generated_code.stub_code)
