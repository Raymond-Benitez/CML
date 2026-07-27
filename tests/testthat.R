library(testthat)
library(CML)

test_check("CML")

test <- CMLmod::cml(asiadf, targets = c(1,2))
