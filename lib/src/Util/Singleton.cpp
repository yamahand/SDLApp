#include "Singleton.h"

namespace lib {
constexpr size_t kMaxFinalizersSize = 256;
size_t g_finalizers_size            = 0;

SingletonFinalizer::FinalizerFunc g_finalizers[kMaxFinalizersSize];

void SingletonFinalizer::AddFinalizer(FinalizerFunc func) {
    if (g_finalizers_size < kMaxFinalizersSize) {
        g_finalizers[g_finalizers_size++] = func;
    } else {
        // TODO: エラーログ出す
    }
}

void SingletonFinalizer::Finalize() {
    for (size_t i = g_finalizers_size; i > 0; --i) {
        (*g_finalizers[i - 1])();
    }
    g_finalizers_size = 0;
}
}  // namespace lib
