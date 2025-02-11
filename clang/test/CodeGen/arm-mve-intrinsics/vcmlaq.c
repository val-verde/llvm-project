// REQUIRES: aarch64-registered-target || arm-registered-target

// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple thumbv8.1m.main-none-none-eabi -target-feature +mve.fp -mfloat-abi hard -fallow-half-arguments-and-returns -O0 -disable-O0-optnone -S -emit-llvm -o - %s | opt -S -mem2reg | FileCheck %s
// RUN: %clang_cc1 -triple thumbv8.1m.main-none-none-eabi -target-feature +mve.fp -mfloat-abi hard -fallow-half-arguments-and-returns -O0 -disable-O0-optnone -DPOLYMORPHIC -S -emit-llvm -o - %s | opt -S -mem2reg | FileCheck %s

#include <arm_mve.h>

// CHECK-LABEL: @test_vcmlaq_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.v8f16(i32 0, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]])
// CHECK-NEXT:    ret <8 x half> [[TMP0]]
//
float16x8_t test_vcmlaq_f16(float16x8_t a, float16x8_t b, float16x8_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq(a, b, c);
#else
    return vcmlaq_f16(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.v4f32(i32 0, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]])
// CHECK-NEXT:    ret <4 x float> [[TMP0]]
//
float32x4_t test_vcmlaq_f32(float32x4_t a, float32x4_t b, float32x4_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq(a, b, c);
#else
    return vcmlaq_f32(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot90_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.v8f16(i32 1, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]])
// CHECK-NEXT:    ret <8 x half> [[TMP0]]
//
float16x8_t test_vcmlaq_rot90_f16(float16x8_t a, float16x8_t b, float16x8_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot90(a, b, c);
#else
    return vcmlaq_rot90_f16(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot90_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.v4f32(i32 1, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]])
// CHECK-NEXT:    ret <4 x float> [[TMP0]]
//
float32x4_t test_vcmlaq_rot90_f32(float32x4_t a, float32x4_t b, float32x4_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot90(a, b, c);
#else
    return vcmlaq_rot90_f32(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot180_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.v8f16(i32 2, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]])
// CHECK-NEXT:    ret <8 x half> [[TMP0]]
//
float16x8_t test_vcmlaq_rot180_f16(float16x8_t a, float16x8_t b, float16x8_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot180(a, b, c);
#else
    return vcmlaq_rot180_f16(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot180_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.v4f32(i32 2, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]])
// CHECK-NEXT:    ret <4 x float> [[TMP0]]
//
float32x4_t test_vcmlaq_rot180_f32(float32x4_t a, float32x4_t b, float32x4_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot180(a, b, c);
#else
    return vcmlaq_rot180_f32(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot270_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.v8f16(i32 3, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]])
// CHECK-NEXT:    ret <8 x half> [[TMP0]]
//
float16x8_t test_vcmlaq_rot270_f16(float16x8_t a, float16x8_t b, float16x8_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot270(a, b, c);
#else
    return vcmlaq_rot270_f16(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot270_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.v4f32(i32 3, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]])
// CHECK-NEXT:    ret <4 x float> [[TMP0]]
//
float32x4_t test_vcmlaq_rot270_f32(float32x4_t a, float32x4_t b, float32x4_t c)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot270(a, b, c);
#else
    return vcmlaq_rot270_f32(a, b, c);
#endif
}

// CHECK-LABEL: @test_vcmlaq_m_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.predicated.v8f16.v8i1(i32 0, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]], <8 x i1> [[TMP1]])
// CHECK-NEXT:    ret <8 x half> [[TMP2]]
//
float16x8_t test_vcmlaq_m_f16(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_m(a, b, c, p);
#else
    return vcmlaq_m_f16(a, b, c, p);
#endif
}

// CHECK-LABEL: @test_vcmlaq_m_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.predicated.v4f32.v4i1(i32 0, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]], <4 x i1> [[TMP1]])
// CHECK-NEXT:    ret <4 x float> [[TMP2]]
//
float32x4_t test_vcmlaq_m_f32(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_m(a, b, c, p);
#else
    return vcmlaq_m_f32(a, b, c, p);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot90_m_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.predicated.v8f16.v8i1(i32 1, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]], <8 x i1> [[TMP1]])
// CHECK-NEXT:    ret <8 x half> [[TMP2]]
//
float16x8_t test_vcmlaq_rot90_m_f16(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot90_m(a, b, c, p);
#else
    return vcmlaq_rot90_m_f16(a, b, c, p);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot90_m_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.predicated.v4f32.v4i1(i32 1, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]], <4 x i1> [[TMP1]])
// CHECK-NEXT:    ret <4 x float> [[TMP2]]
//
float32x4_t test_vcmlaq_rot90_m_f32(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot90_m(a, b, c, p);
#else
    return vcmlaq_rot90_m_f32(a, b, c, p);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot180_m_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.predicated.v8f16.v8i1(i32 2, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]], <8 x i1> [[TMP1]])
// CHECK-NEXT:    ret <8 x half> [[TMP2]]
//
float16x8_t test_vcmlaq_rot180_m_f16(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot180_m(a, b, c, p);
#else
    return vcmlaq_rot180_m_f16(a, b, c, p);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot180_m_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.predicated.v4f32.v4i1(i32 2, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]], <4 x i1> [[TMP1]])
// CHECK-NEXT:    ret <4 x float> [[TMP2]]
//
float32x4_t test_vcmlaq_rot180_m_f32(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot180_m(a, b, c, p);
#else
    return vcmlaq_rot180_m_f32(a, b, c, p);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot270_m_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x half> @llvm.arm.mve.vcmlaq.predicated.v8f16.v8i1(i32 3, <8 x half> [[A:%.*]], <8 x half> [[B:%.*]], <8 x half> [[C:%.*]], <8 x i1> [[TMP1]])
// CHECK-NEXT:    ret <8 x half> [[TMP2]]
//
float16x8_t test_vcmlaq_rot270_m_f16(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot270_m(a, b, c, p);
#else
    return vcmlaq_rot270_m_f16(a, b, c, p);
#endif
}

// CHECK-LABEL: @test_vcmlaq_rot270_m_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP1:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP0]])
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x float> @llvm.arm.mve.vcmlaq.predicated.v4f32.v4i1(i32 3, <4 x float> [[A:%.*]], <4 x float> [[B:%.*]], <4 x float> [[C:%.*]], <4 x i1> [[TMP1]])
// CHECK-NEXT:    ret <4 x float> [[TMP2]]
//
float32x4_t test_vcmlaq_rot270_m_f32(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p)
{
#ifdef POLYMORPHIC
    return vcmlaq_rot270_m(a, b, c, p);
#else
    return vcmlaq_rot270_m_f32(a, b, c, p);
#endif
}

