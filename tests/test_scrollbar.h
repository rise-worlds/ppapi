// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PAPPI_TESTS_TEST_SCROLLBAR_H_
#define PAPPI_TESTS_TEST_SCROLLBAR_H_

#include "ppapi/tests/test_case.h"

class TestScrollbar : public TestCase {
 public:
  TestScrollbar(TestInstance* instance);

  // TestCase implementation.
  virtual void RunTest();
  virtual void ScrollbarValueChanged(PP_Resource scrollbar, uint32_t value);

 private:
  std::string TestHandleEvent();

  PP_Resource scrollbar_id_;
  bool scrollbar_value_changed_;
};

#endif  // PAPPI_TESTS_TEST_SCROLLBAR_H_
