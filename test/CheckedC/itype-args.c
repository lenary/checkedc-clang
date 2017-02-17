// RUN: %clang_cc1 -fcheckedc-extension -emit-llvm %s -o %t
// RUN: %clang_cc1 -fcheckedc-extension -ast-dump %s | FileCheck %s

void f1(int *p : itype(_Ptr<int>));
_Ptr<int> f2(void);

_Ptr<int> g0 = 0;
int *g1 : itype(_Ptr<int>) = 0;


void ff1(_Ptr<int> p) {
	f1(p);
    // CHECK: CallExpr
    // CHECK: 'f1' 'void (int * : _Ptr<int>)'
    // CHECK: ImplicitCastExpr
    // CHECK-SAME: 'int *' <BitCast>
    // CHECK-NEXT: ImplicitCastExpr
    // CHECK-SAME: '_Ptr<int>' <LValueToRValue>
    // CHECK-NEXT: DeclRefExpr
    // CHECK-SAME: 'p' '_Ptr<int>'

    g1 = p;
    // CHECK: BinaryOperator
    // CHECK-SAME: 'int *' '='
    // CHECK-NEXT: DeclRefExpr
    // CHECK-SAME: 'g1' 'int *'
    // CHECK: ImplicitCastExpr
    // CHECK-SAME: 'int *' <BitCast>
    // CHECK-NEXT: ImplicitCastExpr
    // CHECK-SAME: '_Ptr<int>' <LValueToRValue>
    // CHECK-NEXT: DeclRefExpr
    // CHECK-SAME: 'p' '_Ptr<int>'
}



void ff2(void) {
  f1(f2());
  // CHECK: CallExpr
  // CHECK: 'f1' 'void (int * : _Ptr<int>)'
  // CHECK: ImplicitCastExpr
  // CHECK-SAME: 'int *' <BitCast>
  // CHECK-NEXT: CallExpr
  // CHECK-SAME: '_Ptr<int>'

  g1 = f2();
  // CHECK: BinaryOperator
  // CHECK-SAME: 'int *' '='
  // CHECK-NEXT: DeclRefExpr
  // CHECK-SAME: 'g1' 'int *'
  // CHECK: ImplicitCastExpr
  // CHECK-SAME: 'int *' <BitCast>
  // CHECK-NEXT: CallExpr
  // CHECK-SAME: '_Ptr<int>'
}