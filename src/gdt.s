global createGDT        ; make the label createGDT visible outside this file

; createGDT - creates a new descriptor table
createGDT:
    lgdt [eax]          ; create the global descriptor table
    ret                 ; return to the calling function
