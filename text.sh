#!/bin/bash

# Liste des fichiers à tester
files=(
    "big_map.cub"
    "empty_map.cub"
    "invalid_chr.cub"
    "invalid_extra_line.cub"
    "invalid_format.ber"
    "invalid_map.cub"
    "invalid_rgb.cub"
    "invalid_rgb_overflow.cub"
    "invalid_texture_path.cub"
    "invalid_texture_path_2.cub"
    "map.cub"
    "small_map.cub"
    "tab_by_the_right.cub"
)

# Boucle pour tester chaque fichier
for file in "${files[@]}"; do
    echo "Testing $file..."
    ./cube "$file"
    echo "============================================="
done
