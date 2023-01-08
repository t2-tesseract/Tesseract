make -C limine
mkdir -p iso_root
cp -v kernel.elf limine.cfg limine/limine.sys       limine/limine-cd.bin limine/limine-eltorito-efi.bin iso_root/
xorriso -as mkisofs -b limine-cd.bin         -no-emul-boot -boot-load-size 4 -boot-info-table         --efi-boot limine-eltorito-efi.bin         -efi-boot-part --efi-boot-image --protective-msdos-label         iso_root -o tesseract.iso
./limine/limine-install tesseract.iso
