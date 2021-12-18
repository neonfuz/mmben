{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  buildInputs = [
    SDL2
    SDL2_image
    gnumake
    optipng
  ];
}
