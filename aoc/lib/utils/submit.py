import re
import os
from pathlib import Path

def extract_optional_includes(file_path):
    """Extract includes between optional markers and resolve them."""
    with open(file_path, 'r') as f:
        content = f.read()

    # Find optional section
    optional_pattern = r'/\* START OPTIONAL INCLUDES \*/(.*?)/\* END OPTIONAL INCLUDES \*/'
    optional_match = re.search(optional_pattern, content, re.DOTALL)
    
    if not optional_match:
        return None
    
    # Extract include statements
    includes = re.findall(r'#include\s*"([^"]+)"', optional_match.group(1))
    
    # Resolve each include
    resolved_content = []
    base_path = Path(file_path).parent
    
    for include in includes:
        include_path = base_path / include
        if include_path.exists():
            with open(include_path, 'r') as f:
                resolved_content.append(f.read())
        else:
            print(f"Warning: Include file not found: {include}")
    
    return '\n'.join(resolved_content)

def process_file(input_file, output_file):
    """Process the input file and create a submission version."""
    with open(input_file, 'r') as f:
        content = f.read()
    
    # Get resolved includes
    resolved_includes = extract_optional_includes(input_file)
    
    if resolved_includes is None:
        print("No optional includes section found")
        return
    
    # Replace the optional section with resolved includes
    new_content = re.sub(
        r'/\* START OPTIONAL INCLUDES \*/.*?/\* END OPTIONAL INCLUDES \*/',
        lambda m: resolved_includes.replace('\\', '\\\\'),  # Double backslashes instead of full escape
        content,
        flags=re.DOTALL
    )
    
    # Write the processed content
    with open(output_file, 'w') as f:
        f.write(new_content)

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: python submit.py input_file output_file")
        sys.exit(1)
    
    process_file(sys.argv[1], sys.argv[2])