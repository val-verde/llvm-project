// REQUIRES: aarch64-registered-target || arm-registered-target

// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - -x c++ %s | FileCheck %s
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - -x c++ %s | FileCheck %s
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -fallow-half-arguments-and-returns -fsyntax-only -verify -verify-ignore-unexpected=error %s
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve -fallow-half-arguments-and-returns -fsyntax-only -verify=overload -verify-ignore-unexpected=error %s

#include <arm_sve.h>

#ifdef SVE_OVERLOADED_FORMS
// A simple used,unused... macro, long enough to represent any SVE builtin.
#define SVE_ACLE_FUNC(A1,A2_UNUSED,A3,A4_UNUSED) A1##A3
#else
#define SVE_ACLE_FUNC(A1,A2,A3,A4) A1##A2##A3##A4
#endif

svint8_t test_svmaxp_s8_m(svbool_t pg, svint8_t op1, svint8_t op2)
{
  // CHECK-LABEL: test_svmaxp_s8_m
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 16 x i8> @llvm.aarch64.sve.smaxp.nxv16i8(<vscale x 16 x i1> %pg, <vscale x 16 x i8> %op1, <vscale x 16 x i8> %op2)
  // CHECK: ret <vscale x 16 x i8> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s8_m'}}
  return SVE_ACLE_FUNC(svmaxp,_s8,_m,)(pg, op1, op2);
}

svint16_t test_svmaxp_s16_m(svbool_t pg, svint16_t op1, svint16_t op2)
{
  // CHECK-LABEL: test_svmaxp_s16_m
  // CHECK: %[[PG:.*]] = call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 8 x i16> @llvm.aarch64.sve.smaxp.nxv8i16(<vscale x 8 x i1> %[[PG]], <vscale x 8 x i16> %op1, <vscale x 8 x i16> %op2)
  // CHECK: ret <vscale x 8 x i16> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s16_m'}}
  return SVE_ACLE_FUNC(svmaxp,_s16,_m,)(pg, op1, op2);
}

svint32_t test_svmaxp_s32_m(svbool_t pg, svint32_t op1, svint32_t op2)
{
  // CHECK-LABEL: test_svmaxp_s32_m
  // CHECK: %[[PG:.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.smaxp.nxv4i32(<vscale x 4 x i1> %[[PG]], <vscale x 4 x i32> %op1, <vscale x 4 x i32> %op2)
  // CHECK: ret <vscale x 4 x i32> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s32_m'}}
  return SVE_ACLE_FUNC(svmaxp,_s32,_m,)(pg, op1, op2);
}

svint64_t test_svmaxp_s64_m(svbool_t pg, svint64_t op1, svint64_t op2)
{
  // CHECK-LABEL: test_svmaxp_s64_m
  // CHECK: %[[PG:.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 2 x i64> @llvm.aarch64.sve.smaxp.nxv2i64(<vscale x 2 x i1> %[[PG]], <vscale x 2 x i64> %op1, <vscale x 2 x i64> %op2)
  // CHECK: ret <vscale x 2 x i64> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s64_m'}}
  return SVE_ACLE_FUNC(svmaxp,_s64,_m,)(pg, op1, op2);
}

svuint8_t test_svmaxp_u8_m(svbool_t pg, svuint8_t op1, svuint8_t op2)
{
  // CHECK-LABEL: test_svmaxp_u8_m
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 16 x i8> @llvm.aarch64.sve.umaxp.nxv16i8(<vscale x 16 x i1> %pg, <vscale x 16 x i8> %op1, <vscale x 16 x i8> %op2)
  // CHECK: ret <vscale x 16 x i8> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u8_m'}}
  return SVE_ACLE_FUNC(svmaxp,_u8,_m,)(pg, op1, op2);
}

svuint16_t test_svmaxp_u16_m(svbool_t pg, svuint16_t op1, svuint16_t op2)
{
  // CHECK-LABEL: test_svmaxp_u16_m
  // CHECK: %[[PG:.*]] = call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 8 x i16> @llvm.aarch64.sve.umaxp.nxv8i16(<vscale x 8 x i1> %[[PG]], <vscale x 8 x i16> %op1, <vscale x 8 x i16> %op2)
  // CHECK: ret <vscale x 8 x i16> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u16_m'}}
  return SVE_ACLE_FUNC(svmaxp,_u16,_m,)(pg, op1, op2);
}

svuint32_t test_svmaxp_u32_m(svbool_t pg, svuint32_t op1, svuint32_t op2)
{
  // CHECK-LABEL: test_svmaxp_u32_m
  // CHECK: %[[PG:.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.umaxp.nxv4i32(<vscale x 4 x i1> %[[PG]], <vscale x 4 x i32> %op1, <vscale x 4 x i32> %op2)
  // CHECK: ret <vscale x 4 x i32> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u32_m'}}
  return SVE_ACLE_FUNC(svmaxp,_u32,_m,)(pg, op1, op2);
}

svuint64_t test_svmaxp_u64_m(svbool_t pg, svuint64_t op1, svuint64_t op2)
{
  // CHECK-LABEL: test_svmaxp_u64_m
  // CHECK: %[[PG:.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 2 x i64> @llvm.aarch64.sve.umaxp.nxv2i64(<vscale x 2 x i1> %[[PG]], <vscale x 2 x i64> %op1, <vscale x 2 x i64> %op2)
  // CHECK: ret <vscale x 2 x i64> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u64_m'}}
  return SVE_ACLE_FUNC(svmaxp,_u64,_m,)(pg, op1, op2);
}

svint8_t test_svmaxp_s8_x(svbool_t pg, svint8_t op1, svint8_t op2)
{
  // CHECK-LABEL: test_svmaxp_s8_x
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 16 x i8> @llvm.aarch64.sve.smaxp.nxv16i8(<vscale x 16 x i1> %pg, <vscale x 16 x i8> %op1, <vscale x 16 x i8> %op2)
  // CHECK: ret <vscale x 16 x i8> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s8_x'}}
  return SVE_ACLE_FUNC(svmaxp,_s8,_x,)(pg, op1, op2);
}

svint16_t test_svmaxp_s16_x(svbool_t pg, svint16_t op1, svint16_t op2)
{
  // CHECK-LABEL: test_svmaxp_s16_x
  // CHECK: %[[PG:.*]] = call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 8 x i16> @llvm.aarch64.sve.smaxp.nxv8i16(<vscale x 8 x i1> %[[PG]], <vscale x 8 x i16> %op1, <vscale x 8 x i16> %op2)
  // CHECK: ret <vscale x 8 x i16> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s16_x'}}
  return SVE_ACLE_FUNC(svmaxp,_s16,_x,)(pg, op1, op2);
}

svint32_t test_svmaxp_s32_x(svbool_t pg, svint32_t op1, svint32_t op2)
{
  // CHECK-LABEL: test_svmaxp_s32_x
  // CHECK: %[[PG:.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.smaxp.nxv4i32(<vscale x 4 x i1> %[[PG]], <vscale x 4 x i32> %op1, <vscale x 4 x i32> %op2)
  // CHECK: ret <vscale x 4 x i32> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s32_x'}}
  return SVE_ACLE_FUNC(svmaxp,_s32,_x,)(pg, op1, op2);
}

svint64_t test_svmaxp_s64_x(svbool_t pg, svint64_t op1, svint64_t op2)
{
  // CHECK-LABEL: test_svmaxp_s64_x
  // CHECK: %[[PG:.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 2 x i64> @llvm.aarch64.sve.smaxp.nxv2i64(<vscale x 2 x i1> %[[PG]], <vscale x 2 x i64> %op1, <vscale x 2 x i64> %op2)
  // CHECK: ret <vscale x 2 x i64> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_s64_x'}}
  return SVE_ACLE_FUNC(svmaxp,_s64,_x,)(pg, op1, op2);
}

svuint8_t test_svmaxp_u8_x(svbool_t pg, svuint8_t op1, svuint8_t op2)
{
  // CHECK-LABEL: test_svmaxp_u8_x
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 16 x i8> @llvm.aarch64.sve.umaxp.nxv16i8(<vscale x 16 x i1> %pg, <vscale x 16 x i8> %op1, <vscale x 16 x i8> %op2)
  // CHECK: ret <vscale x 16 x i8> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u8_x'}}
  return SVE_ACLE_FUNC(svmaxp,_u8,_x,)(pg, op1, op2);
}

svuint16_t test_svmaxp_u16_x(svbool_t pg, svuint16_t op1, svuint16_t op2)
{
  // CHECK-LABEL: test_svmaxp_u16_x
  // CHECK: %[[PG:.*]] = call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 8 x i16> @llvm.aarch64.sve.umaxp.nxv8i16(<vscale x 8 x i1> %[[PG]], <vscale x 8 x i16> %op1, <vscale x 8 x i16> %op2)
  // CHECK: ret <vscale x 8 x i16> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u16_x'}}
  return SVE_ACLE_FUNC(svmaxp,_u16,_x,)(pg, op1, op2);
}

svuint32_t test_svmaxp_u32_x(svbool_t pg, svuint32_t op1, svuint32_t op2)
{
  // CHECK-LABEL: test_svmaxp_u32_x
  // CHECK: %[[PG:.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.umaxp.nxv4i32(<vscale x 4 x i1> %[[PG]], <vscale x 4 x i32> %op1, <vscale x 4 x i32> %op2)
  // CHECK: ret <vscale x 4 x i32> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u32_x'}}
  return SVE_ACLE_FUNC(svmaxp,_u32,_x,)(pg, op1, op2);
}

svuint64_t test_svmaxp_u64_x(svbool_t pg, svuint64_t op1, svuint64_t op2)
{
  // CHECK-LABEL: test_svmaxp_u64_x
  // CHECK: %[[PG:.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 2 x i64> @llvm.aarch64.sve.umaxp.nxv2i64(<vscale x 2 x i1> %[[PG]], <vscale x 2 x i64> %op1, <vscale x 2 x i64> %op2)
  // CHECK: ret <vscale x 2 x i64> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_u64_x'}}
  return SVE_ACLE_FUNC(svmaxp,_u64,_x,)(pg, op1, op2);
}

svfloat16_t test_svmaxp_f16_m(svbool_t pg, svfloat16_t op1, svfloat16_t op2)
{
  // CHECK-LABEL: test_svmaxp_f16_m
  // CHECK: %[[PG:.*]] = call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 8 x half> @llvm.aarch64.sve.fmaxp.nxv8f16(<vscale x 8 x i1> %[[PG]], <vscale x 8 x half> %op1, <vscale x 8 x half> %op2)
  // CHECK: ret <vscale x 8 x half> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_f16_m'}}
  return SVE_ACLE_FUNC(svmaxp,_f16,_m,)(pg, op1, op2);
}

svfloat32_t test_svmaxp_f32_m(svbool_t pg, svfloat32_t op1, svfloat32_t op2)
{
  // CHECK-LABEL: test_svmaxp_f32_m
  // CHECK: %[[PG:.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 4 x float> @llvm.aarch64.sve.fmaxp.nxv4f32(<vscale x 4 x i1> %[[PG]], <vscale x 4 x float> %op1, <vscale x 4 x float> %op2)
  // CHECK: ret <vscale x 4 x float> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_f32_m'}}
  return SVE_ACLE_FUNC(svmaxp,_f32,_m,)(pg, op1, op2);
}

svfloat64_t test_svmaxp_f64_m(svbool_t pg, svfloat64_t op1, svfloat64_t op2)
{
  // CHECK-LABEL: test_svmaxp_f64_m
  // CHECK: %[[PG:.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 2 x double> @llvm.aarch64.sve.fmaxp.nxv2f64(<vscale x 2 x i1> %[[PG]], <vscale x 2 x double> %op1, <vscale x 2 x double> %op2)
  // CHECK: ret <vscale x 2 x double> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_m'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_f64_m'}}
  return SVE_ACLE_FUNC(svmaxp,_f64,_m,)(pg, op1, op2);
}

svfloat16_t test_svmaxp_f16_x(svbool_t pg, svfloat16_t op1, svfloat16_t op2)
{
  // CHECK-LABEL: test_svmaxp_f16_x
  // CHECK: %[[PG:.*]] = call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 8 x half> @llvm.aarch64.sve.fmaxp.nxv8f16(<vscale x 8 x i1> %[[PG]], <vscale x 8 x half> %op1, <vscale x 8 x half> %op2)
  // CHECK: ret <vscale x 8 x half> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_f16_x'}}
  return SVE_ACLE_FUNC(svmaxp,_f16,_x,)(pg, op1, op2);
}

svfloat32_t test_svmaxp_f32_x(svbool_t pg, svfloat32_t op1, svfloat32_t op2)
{
  // CHECK-LABEL: test_svmaxp_f32_x
  // CHECK: %[[PG:.*]] = call <vscale x 4 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv4i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 4 x float> @llvm.aarch64.sve.fmaxp.nxv4f32(<vscale x 4 x i1> %[[PG]], <vscale x 4 x float> %op1, <vscale x 4 x float> %op2)
  // CHECK: ret <vscale x 4 x float> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_f32_x'}}
  return SVE_ACLE_FUNC(svmaxp,_f32,_x,)(pg, op1, op2);
}

svfloat64_t test_svmaxp_f64_x(svbool_t pg, svfloat64_t op1, svfloat64_t op2)
{
  // CHECK-LABEL: test_svmaxp_f64_x
  // CHECK: %[[PG:.*]] = call <vscale x 2 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv2i1(<vscale x 16 x i1> %pg)
  // CHECK: %[[INTRINSIC:.*]] = call <vscale x 2 x double> @llvm.aarch64.sve.fmaxp.nxv2f64(<vscale x 2 x i1> %[[PG]], <vscale x 2 x double> %op1, <vscale x 2 x double> %op2)
  // CHECK: ret <vscale x 2 x double> %[[INTRINSIC]]
  // overload-warning@+2 {{implicit declaration of function 'svmaxp_x'}}
  // expected-warning@+1 {{implicit declaration of function 'svmaxp_f64_x'}}
  return SVE_ACLE_FUNC(svmaxp,_f64,_x,)(pg, op1, op2);
}
