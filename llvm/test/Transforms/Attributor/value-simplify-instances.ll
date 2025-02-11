; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --function-signature --check-attributes --check-globals
; RUN: opt -attributor -enable-new-pm=0 -attributor-manifest-internal  -attributor-max-iterations-verify -attributor-annotate-decl-cs -attributor-max-iterations=6 -S < %s | FileCheck %s --check-prefixes=CHECK,NOT_CGSCC_NPM,NOT_CGSCC_OPM,NOT_TUNIT_NPM,IS__TUNIT____,IS________OPM,IS__TUNIT_OPM
; RUN: opt -aa-pipeline=basic-aa -passes=attributor -attributor-manifest-internal  -attributor-max-iterations-verify -attributor-annotate-decl-cs -attributor-max-iterations=6 -S < %s | FileCheck %s --check-prefixes=CHECK,NOT_CGSCC_OPM,NOT_CGSCC_NPM,NOT_TUNIT_OPM,IS__TUNIT____,IS________NPM,IS__TUNIT_NPM
; RUN: opt -attributor-cgscc -enable-new-pm=0 -attributor-manifest-internal  -attributor-annotate-decl-cs -S < %s | FileCheck %s --check-prefixes=CHECK,NOT_TUNIT_NPM,NOT_TUNIT_OPM,NOT_CGSCC_NPM,IS__CGSCC____,IS________OPM,IS__CGSCC_OPM
; RUN: opt -aa-pipeline=basic-aa -passes=attributor-cgscc -attributor-manifest-internal  -attributor-annotate-decl-cs -S < %s | FileCheck %s --check-prefixes=CHECK,NOT_TUNIT_NPM,NOT_TUNIT_OPM,NOT_CGSCC_OPM,IS__CGSCC____,IS________NPM,IS__CGSCC_NPM

target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"

declare i1* @geti1Ptr()

; Make sure we do *not* return true.
;.
; CHECK: @[[G1:[a-zA-Z0-9_$"\\.-]+]] = private global i1* undef
; CHECK: @[[G2:[a-zA-Z0-9_$"\\.-]+]] = private global i1* undef
; CHECK: @[[G3:[a-zA-Z0-9_$"\\.-]+]] = private global i1 undef
;.
define internal i1 @recursive_inst_comparator(i1* %a, i1* %b) {
; IS__TUNIT____: Function Attrs: nofree nosync nounwind readnone willreturn
; IS__TUNIT____-LABEL: define {{[^@]+}}@recursive_inst_comparator
; IS__TUNIT____-SAME: (i1* noalias nofree readnone [[A:%.*]], i1* noalias nofree readnone [[B:%.*]]) #[[ATTR0:[0-9]+]] {
; IS__TUNIT____-NEXT:    [[CMP:%.*]] = icmp eq i1* [[A]], [[B]]
; IS__TUNIT____-NEXT:    ret i1 [[CMP]]
;
; IS__CGSCC____: Function Attrs: nofree norecurse nosync nounwind readnone willreturn
; IS__CGSCC____-LABEL: define {{[^@]+}}@recursive_inst_comparator
; IS__CGSCC____-SAME: (i1* noalias nofree readnone [[A:%.*]], i1* noalias nofree readnone [[B:%.*]]) #[[ATTR0:[0-9]+]] {
; IS__CGSCC____-NEXT:    [[CMP:%.*]] = icmp eq i1* [[A]], [[B]]
; IS__CGSCC____-NEXT:    ret i1 [[CMP]]
;
  %cmp = icmp eq i1* %a, %b
  ret i1 %cmp
}

define internal i1 @recursive_inst_generator(i1 %c, i1* %p) {
; IS__TUNIT____-LABEL: define {{[^@]+}}@recursive_inst_generator
; IS__TUNIT____-SAME: (i1 [[C:%.*]], i1* nofree [[P:%.*]]) {
; IS__TUNIT____-NEXT:    [[A:%.*]] = call i1* @geti1Ptr()
; IS__TUNIT____-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; IS__TUNIT____:       t:
; IS__TUNIT____-NEXT:    [[R1:%.*]] = call i1 @recursive_inst_comparator(i1* noalias nofree readnone [[A]], i1* noalias nofree readnone [[P]]) #[[ATTR4:[0-9]+]]
; IS__TUNIT____-NEXT:    ret i1 [[R1]]
; IS__TUNIT____:       f:
; IS__TUNIT____-NEXT:    [[R2:%.*]] = call i1 @recursive_inst_generator(i1 noundef true, i1* nofree [[A]])
; IS__TUNIT____-NEXT:    ret i1 [[R2]]
;
; IS__CGSCC____-LABEL: define {{[^@]+}}@recursive_inst_generator
; IS__CGSCC____-SAME: (i1 [[C:%.*]], i1* nofree [[P:%.*]]) {
; IS__CGSCC____-NEXT:    [[A:%.*]] = call i1* @geti1Ptr()
; IS__CGSCC____-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; IS__CGSCC____:       t:
; IS__CGSCC____-NEXT:    [[R1:%.*]] = call i1 @recursive_inst_comparator(i1* noalias nofree readnone [[A]], i1* noalias nofree readnone [[P]])
; IS__CGSCC____-NEXT:    ret i1 [[R1]]
; IS__CGSCC____:       f:
; IS__CGSCC____-NEXT:    [[R2:%.*]] = call i1 @recursive_inst_generator(i1 noundef true, i1* nofree [[A]])
; IS__CGSCC____-NEXT:    ret i1 [[R2]]
;
  %a = call i1* @geti1Ptr()
  br i1 %c, label %t, label %f
t:
  %r1 = call i1 @recursive_inst_comparator(i1* %a, i1* %p)
  ret i1 %r1
f:
  %r2 = call i1 @recursive_inst_generator(i1 true, i1* %a)
  ret i1 %r2
}

; FIXME: This should *not* return true.
define i1 @recursive_inst_generator_caller(i1 %c) {
; CHECK-LABEL: define {{[^@]+}}@recursive_inst_generator_caller
; CHECK-SAME: (i1 [[C:%.*]]) {
; CHECK-NEXT:    [[CALL:%.*]] = call i1 @recursive_inst_generator(i1 [[C]], i1* undef)
; CHECK-NEXT:    ret i1 [[CALL]]
;
  %call = call i1 @recursive_inst_generator(i1 %c, i1* undef)
  ret i1 %call
}

; Make sure we do *not* return true.
define internal i1 @recursive_inst_compare(i1 %c, i1* %p) {
; CHECK-LABEL: define {{[^@]+}}@recursive_inst_compare
; CHECK-SAME: (i1 [[C:%.*]], i1* [[P:%.*]]) {
; CHECK-NEXT:    [[A:%.*]] = call i1* @geti1Ptr()
; CHECK-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; CHECK:       t:
; CHECK-NEXT:    [[CMP:%.*]] = icmp eq i1* [[A]], [[P]]
; CHECK-NEXT:    ret i1 [[CMP]]
; CHECK:       f:
; CHECK-NEXT:    [[CALL:%.*]] = call i1 @recursive_inst_compare(i1 noundef true, i1* [[A]])
; CHECK-NEXT:    ret i1 [[CALL]]
;
  %a = call i1* @geti1Ptr()
  br i1 %c, label %t, label %f
t:
  %cmp = icmp eq i1* %a, %p
  ret i1 %cmp
f:
  %call = call i1 @recursive_inst_compare(i1 true, i1* %a)
  ret i1 %call
}

; FIXME: This should *not* return true.
define i1 @recursive_inst_compare_caller(i1 %c) {
; CHECK-LABEL: define {{[^@]+}}@recursive_inst_compare_caller
; CHECK-SAME: (i1 [[C:%.*]]) {
; CHECK-NEXT:    [[CALL:%.*]] = call i1 @recursive_inst_compare(i1 [[C]], i1* undef)
; CHECK-NEXT:    ret i1 [[CALL]]
;
  %call = call i1 @recursive_inst_compare(i1 %c, i1* undef)
  ret i1 %call
}

; Make sure we do *not* return true.
define internal i1 @recursive_alloca_compare(i1 %c, i1* %p) {
; CHECK: Function Attrs: nofree nosync nounwind readnone
; CHECK-LABEL: define {{[^@]+}}@recursive_alloca_compare
; CHECK-SAME: (i1 [[C:%.*]], i1* noalias nofree nonnull readnone [[P:%.*]]) #[[ATTR1:[0-9]+]] {
; CHECK-NEXT:    [[A:%.*]] = alloca i1, align 1
; CHECK-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; CHECK:       t:
; CHECK-NEXT:    [[CMP:%.*]] = icmp eq i1* [[A]], [[P]]
; CHECK-NEXT:    ret i1 [[CMP]]
; CHECK:       f:
; CHECK-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare(i1 noundef true, i1* noalias nofree noundef nonnull readnone dereferenceable(1) [[A]]) #[[ATTR1]]
; CHECK-NEXT:    ret i1 [[CALL]]
;
  %a = alloca i1
  br i1 %c, label %t, label %f
t:
  %cmp = icmp eq i1* %a, %p
  ret i1 %cmp
f:
  %call = call i1 @recursive_alloca_compare(i1 true, i1* %a)
  ret i1 %call
}

; FIXME: This should *not* return true.
define i1 @recursive_alloca_compare_caller(i1 %c) {
; IS__TUNIT____: Function Attrs: nofree nosync nounwind readnone
; IS__TUNIT____-LABEL: define {{[^@]+}}@recursive_alloca_compare_caller
; IS__TUNIT____-SAME: (i1 [[C:%.*]]) #[[ATTR1]] {
; IS__TUNIT____-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare(i1 [[C]], i1* undef) #[[ATTR1]]
; IS__TUNIT____-NEXT:    ret i1 [[CALL]]
;
; IS__CGSCC____: Function Attrs: nofree nosync nounwind readnone
; IS__CGSCC____-LABEL: define {{[^@]+}}@recursive_alloca_compare_caller
; IS__CGSCC____-SAME: (i1 [[C:%.*]]) #[[ATTR1]] {
; IS__CGSCC____-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare(i1 [[C]], i1* undef) #[[ATTR4:[0-9]+]]
; IS__CGSCC____-NEXT:    ret i1 [[CALL]]
;
  %call = call i1 @recursive_alloca_compare(i1 %c, i1* undef)
  ret i1 %call
}

; Make sure we do *not* simplify this to return 0 or 1, return 42 is ok though.
define internal i8 @recursive_alloca_load_return(i1 %c, i8* %p, i8 %v) {
; CHECK: Function Attrs: argmemonly nofree nosync nounwind
; CHECK-LABEL: define {{[^@]+}}@recursive_alloca_load_return
; CHECK-SAME: (i1 [[C:%.*]], i8* nocapture nofree nonnull readonly [[P:%.*]], i8 noundef [[V:%.*]]) #[[ATTR2:[0-9]+]] {
; CHECK-NEXT:    [[A:%.*]] = alloca i8, align 1
; CHECK-NEXT:    store i8 [[V]], i8* [[A]], align 1
; CHECK-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; CHECK:       t:
; CHECK-NEXT:    store i8 0, i8* [[A]], align 1
; CHECK-NEXT:    [[L:%.*]] = load i8, i8* [[P]], align 1
; CHECK-NEXT:    ret i8 [[L]]
; CHECK:       f:
; CHECK-NEXT:    [[CALL:%.*]] = call i8 @recursive_alloca_load_return(i1 noundef true, i8* noalias nocapture nofree noundef nonnull readonly dereferenceable(1) [[A]], i8 noundef 1) #[[ATTR3:[0-9]+]]
; CHECK-NEXT:    ret i8 [[CALL]]
;
  %a = alloca i8
  store i8 %v, i8* %a
  br i1 %c, label %t, label %f
t:
  store i8 0, i8* %a
  %l = load i8, i8* %p
  ret i8 %l
f:
  %call = call i8 @recursive_alloca_load_return(i1 true, i8* %a, i8 1)
  ret i8 %call
}

define i8 @recursive_alloca_load_return_caller(i1 %c) {
; IS__TUNIT____: Function Attrs: nofree nosync nounwind readnone
; IS__TUNIT____-LABEL: define {{[^@]+}}@recursive_alloca_load_return_caller
; IS__TUNIT____-SAME: (i1 [[C:%.*]]) #[[ATTR1]] {
; IS__TUNIT____-NEXT:    [[CALL:%.*]] = call i8 @recursive_alloca_load_return(i1 [[C]], i8* undef, i8 noundef 42) #[[ATTR3]]
; IS__TUNIT____-NEXT:    ret i8 [[CALL]]
;
; IS__CGSCC____: Function Attrs: nofree nosync nounwind readnone
; IS__CGSCC____-LABEL: define {{[^@]+}}@recursive_alloca_load_return_caller
; IS__CGSCC____-SAME: (i1 [[C:%.*]]) #[[ATTR1]] {
; IS__CGSCC____-NEXT:    [[CALL:%.*]] = call i8 @recursive_alloca_load_return(i1 [[C]], i8* undef, i8 noundef 42) #[[ATTR5:[0-9]+]]
; IS__CGSCC____-NEXT:    ret i8 [[CALL]]
;
  %call = call i8 @recursive_alloca_load_return(i1 %c, i8* undef, i8 42)
  ret i8 %call
}

@G1 = private global i1* undef
@G2 = private global i1* undef
@G3 = private global i1 undef

; Make sure we do *not* return true.
define internal i1 @recursive_alloca_compare_global1(i1 %c) {
; CHECK: Function Attrs: nofree nosync nounwind
; CHECK-LABEL: define {{[^@]+}}@recursive_alloca_compare_global1
; CHECK-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; CHECK-NEXT:    [[A:%.*]] = alloca i1, align 1
; CHECK-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; CHECK:       t:
; CHECK-NEXT:    [[P:%.*]] = load i1*, i1** @G1, align 8
; CHECK-NEXT:    [[CMP:%.*]] = icmp eq i1* [[A]], [[P]]
; CHECK-NEXT:    ret i1 [[CMP]]
; CHECK:       f:
; CHECK-NEXT:    store i1* [[A]], i1** @G1, align 8
; CHECK-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare_global1(i1 noundef true) #[[ATTR3]]
; CHECK-NEXT:    ret i1 [[CALL]]
;
  %a = alloca i1
  br i1 %c, label %t, label %f
t:
  %p = load i1*, i1** @G1
  %cmp = icmp eq i1* %a, %p
  ret i1 %cmp
f:
  store i1* %a, i1** @G1
  %call = call i1 @recursive_alloca_compare_global1(i1 true)
  ret i1 %call
}

; FIXME: This should *not* return true.
define i1 @recursive_alloca_compare_caller_global1(i1 %c) {
; IS__TUNIT____: Function Attrs: nofree nosync nounwind
; IS__TUNIT____-LABEL: define {{[^@]+}}@recursive_alloca_compare_caller_global1
; IS__TUNIT____-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; IS__TUNIT____-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare_global1(i1 [[C]]) #[[ATTR3]]
; IS__TUNIT____-NEXT:    ret i1 [[CALL]]
;
; IS__CGSCC____: Function Attrs: nofree nosync nounwind
; IS__CGSCC____-LABEL: define {{[^@]+}}@recursive_alloca_compare_caller_global1
; IS__CGSCC____-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; IS__CGSCC____-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare_global1(i1 [[C]]) #[[ATTR5]]
; IS__CGSCC____-NEXT:    ret i1 [[CALL]]
;
  %call = call i1 @recursive_alloca_compare_global1(i1 %c)
  ret i1 %call
}

define internal i1 @recursive_alloca_compare_global2(i1 %c) {
; CHECK: Function Attrs: nofree nosync nounwind
; CHECK-LABEL: define {{[^@]+}}@recursive_alloca_compare_global2
; CHECK-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; CHECK-NEXT:    [[A:%.*]] = alloca i1, align 1
; CHECK-NEXT:    [[P:%.*]] = load i1*, i1** @G2, align 8
; CHECK-NEXT:    store i1* [[A]], i1** @G2, align 8
; CHECK-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; CHECK:       t:
; CHECK-NEXT:    [[CMP:%.*]] = icmp eq i1* [[A]], [[P]]
; CHECK-NEXT:    ret i1 [[CMP]]
; CHECK:       f:
; CHECK-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare_global2(i1 noundef true) #[[ATTR3]]
; CHECK-NEXT:    ret i1 [[CALL]]
;
  %a = alloca i1
  %p = load i1*, i1** @G2
  store i1* %a, i1** @G2
  br i1 %c, label %t, label %f
t:
  %cmp = icmp eq i1* %a, %p
  ret i1 %cmp
f:
  %call = call i1 @recursive_alloca_compare_global2(i1 true)
  ret i1 %call
}

; FIXME: This should *not* return true.
define i1 @recursive_alloca_compare_caller_global2(i1 %c) {
; IS__TUNIT____: Function Attrs: nofree nosync nounwind
; IS__TUNIT____-LABEL: define {{[^@]+}}@recursive_alloca_compare_caller_global2
; IS__TUNIT____-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; IS__TUNIT____-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare_global2(i1 [[C]]) #[[ATTR3]]
; IS__TUNIT____-NEXT:    ret i1 [[CALL]]
;
; IS__CGSCC____: Function Attrs: nofree nosync nounwind
; IS__CGSCC____-LABEL: define {{[^@]+}}@recursive_alloca_compare_caller_global2
; IS__CGSCC____-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; IS__CGSCC____-NEXT:    [[CALL:%.*]] = call i1 @recursive_alloca_compare_global2(i1 [[C]]) #[[ATTR5]]
; IS__CGSCC____-NEXT:    ret i1 [[CALL]]
;
  %call = call i1 @recursive_alloca_compare_global2(i1 %c)
  ret i1 %call
}
define internal i1 @recursive_inst_compare_global3(i1 %c) {
;
; CHECK: Function Attrs: nofree nosync nounwind
; CHECK-LABEL: define {{[^@]+}}@recursive_inst_compare_global3
; CHECK-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; CHECK-NEXT:    [[P:%.*]] = load i1, i1* @G3, align 1
; CHECK-NEXT:    store i1 [[C]], i1* @G3, align 1
; CHECK-NEXT:    br i1 [[C]], label [[T:%.*]], label [[F:%.*]]
; CHECK:       t:
; CHECK-NEXT:    [[CMP:%.*]] = icmp eq i1 [[C]], [[P]]
; CHECK-NEXT:    ret i1 [[CMP]]
; CHECK:       f:
; CHECK-NEXT:    [[CALL:%.*]] = call i1 @recursive_inst_compare_global3(i1 noundef true) #[[ATTR3]]
; CHECK-NEXT:    ret i1 [[CALL]]
;
  %p = load i1, i1* @G3
  store i1 %c, i1* @G3
  br i1 %c, label %t, label %f
t:
  %cmp = icmp eq i1 %c, %p
  ret i1 %cmp
f:
  %call = call i1 @recursive_inst_compare_global3(i1 true)
  ret i1 %call
}

; FIXME: This should *not* return true.
define i1 @recursive_inst_compare_caller_global3(i1 %c) {
; IS__TUNIT____: Function Attrs: nofree nosync nounwind
; IS__TUNIT____-LABEL: define {{[^@]+}}@recursive_inst_compare_caller_global3
; IS__TUNIT____-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; IS__TUNIT____-NEXT:    [[CALL:%.*]] = call i1 @recursive_inst_compare_global3(i1 [[C]]) #[[ATTR3]]
; IS__TUNIT____-NEXT:    ret i1 [[CALL]]
;
; IS__CGSCC____: Function Attrs: nofree nosync nounwind
; IS__CGSCC____-LABEL: define {{[^@]+}}@recursive_inst_compare_caller_global3
; IS__CGSCC____-SAME: (i1 [[C:%.*]]) #[[ATTR3]] {
; IS__CGSCC____-NEXT:    [[CALL:%.*]] = call i1 @recursive_inst_compare_global3(i1 [[C]]) #[[ATTR5]]
; IS__CGSCC____-NEXT:    ret i1 [[CALL]]
;
  %call = call i1 @recursive_inst_compare_global3(i1 %c)
  ret i1 %call
}
;.
; IS__TUNIT____: attributes #[[ATTR0]] = { nofree nosync nounwind readnone willreturn }
; IS__TUNIT____: attributes #[[ATTR1]] = { nofree nosync nounwind readnone }
; IS__TUNIT____: attributes #[[ATTR2]] = { argmemonly nofree nosync nounwind }
; IS__TUNIT____: attributes #[[ATTR3]] = { nofree nosync nounwind }
; IS__TUNIT____: attributes #[[ATTR4]] = { nounwind readnone }
;.
; IS__CGSCC____: attributes #[[ATTR0]] = { nofree norecurse nosync nounwind readnone willreturn }
; IS__CGSCC____: attributes #[[ATTR1]] = { nofree nosync nounwind readnone }
; IS__CGSCC____: attributes #[[ATTR2]] = { argmemonly nofree nosync nounwind }
; IS__CGSCC____: attributes #[[ATTR3]] = { nofree nosync nounwind }
; IS__CGSCC____: attributes #[[ATTR4]] = { nounwind readnone }
; IS__CGSCC____: attributes #[[ATTR5]] = { nounwind }
;.
