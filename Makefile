
.PHONY: build
build:
	pio run

.PHONY: check
check:
	pio check

.PHONY: upload
upload:
	pio run --target upload
