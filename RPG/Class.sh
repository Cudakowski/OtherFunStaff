#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Użycie: $0 <Klasa1> <Klasa2> <Klasa3> ..."
    exit 1
fi

# Create folders if they don't already exist
mkdir -p src include

for name in "$@"
do

# Convert name to uppercase
uppercase_name=$(echo "$name" | tr '[:lower:]' '[:upper:]')

# Creating .cpp file 
cd src
touch "${name}.cpp"
echo "#include \"${name}.h\"
" > "${name}.cpp"

# Creating .h file
cd ../include
touch "${name}.h"

echo "#ifndef ${uppercase_name}_H
#define ${uppercase_name}_H

class ${name} 
{
private:

public:
};

#endif" > "${name}.h"

cd ../

done
