%ifdef ARCH_X86
%include "arch/x86/boot/boot.asinc"
%else
%error "Only X86 architechture supported at this time!"
%endif