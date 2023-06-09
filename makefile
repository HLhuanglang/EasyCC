# Define all variables
TARGET_ECC = ecc
OUTDIR = Build


# Rules
.PHONY: linker
linker:premake
	go build  -gcflags "-N -l" -o ${OUTDIR}/${TARGET_ECC} ecc.go


.PHONY: premake
premake:
	@mkdir -p ${OUTDIR}


.PHONY:clean
clean:
	rm -rf ${OUTDIR}