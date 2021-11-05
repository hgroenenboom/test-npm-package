Push-Location $PSScriptRoot

npm install

Push-Location ./examples/electron

npm install

# Copy native addon to node modules (as if it was actually installed using npm install)
New-Item -ItemType Directory -Force ./node_modules/@hgroenenboom/npmpackage
Copy-Item -Recurse -Force ../../build ./node_modules/@hgroenenboom/npmpackage 

npm run start

Pop-Location
Pop-Location
