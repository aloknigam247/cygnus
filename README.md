# Development on HOLD for Now

# Introduction

Source code browser.

## Components
![components.svg](https://raw.githubusercontent.com/aloknigam247/cygnus/dev/.internal/images/components.svg)

## Build
```bash
source sourceme  
cybuild
```

Generate compile_commands.json
```bash
bear -- make -rB MODE=debug STRICT=no
```

Generate Treesitter
```bash
tree-sitter generate -build --libdir .
```

## Quick Links
> [Release Plan](https://github.com/aloknigam247/cygnus/wiki/Release-Plan-1.0)  
> [Style Guide](https://github.com/aloknigam247/cygnus/wiki/Style-Guide)  
> [Workflow](https://github.com/aloknigam247/cygnus/wiki/Workflow)  
