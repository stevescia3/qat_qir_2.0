// This source file is part of the LLVM Project, which is developed by a community of contributors. 
// Please refer to the LLVM Project homepage for more information. 
#include "ValidationPass.h"
#include "llvm/IR/DerivedTypes.h"

void ValidationPass::pointerChecks(llvm::Value *value) {
    if (auto *ptrType = llvm::dyn_cast<llvm::PointerType>(value->getType())) {
        unsigned addrSpace = ptrType->getAddressSpace();
        // Logic for LLVM 15+ opaque pointers
        if (addrSpace) {
            // Record as "ptr addrspace(N)" 
            addToAllowlist("ptr addrspace(" + std::to_string(addrSpace) + ")");
        } else {
            // Record as "ptr"
            addToAllowlist("ptr");
        }
    } else {
        // Existing logic for typed pointers (LLVM 14 and earlier)
        auto elementType = ptrType->getPointerElementType();
        addToAllowlist(elementType->getAsString());
    }
}

// Other existing methods and logic in the file remain unchanged...