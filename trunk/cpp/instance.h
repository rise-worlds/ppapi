// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_INSTANCE_H_
#define PPAPI_CPP_INSTANCE_H_

#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"

typedef struct _pp_Event PP_Event;
typedef struct _pp_PrintPageNumberRange PP_PrintPageNumberRange;
typedef struct _pp_PrintSettings PP_PrintSettings;
typedef struct _pp_Rect PP_Rect;

namespace pp {

class DeviceContext2D;
class Var;
class Resource;
class URLLoader;

class Instance {
 public:
  explicit Instance(PP_Instance instance);
  virtual ~Instance();

  PP_Instance pp_instance() const { return pp_instance_; }

  // Initializes this plugin with the given arguments. The argument count is in
  // |argc|, the argument names are in |argn|, and the argument values are in
  // |argv|. Returns true on success. Returning false will cause the plugin
  // instance to be deleted and no other functions will be called.
  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);

  // PPP_Instance methods for the plugin to override.
  // See ppp_instance.h for details.
  virtual bool HandleDocumentLoad(const URLLoader& url_loader);
  virtual bool HandleEvent(const PP_Event& event);
  virtual Var GetInstanceObject();
  virtual void ViewChanged(const PP_Rect& position, const PP_Rect& clip);

  // PPP_Printing methods for the plugin to override if it supports printing.
  // See ppp_printing.h for details.
  virtual int32_t PrintBegin(const PP_PrintSettings& print_settings);
  virtual Resource PrintPages(const PP_PrintPageNumberRange* page_ranges,
                              uint32_t page_range_count);
  virtual void PrintEnd();

  // Widget interface.
  virtual void InvalidateWidget(PP_Resource widget_id,
                                const PP_Rect& dirty);

  // Scrollbar interface.
  virtual void ScrollbarValueChanged(PP_Resource scrollbar_id,
                                     uint32_t value);

  // PPB_Instance methods for querying the browser.
  // See ppb_instance.h for details.
  Var GetWindowObject();
  Var GetOwnerElementObject();
  bool BindGraphicsDeviceContext(const DeviceContext2D& context);
  bool IsFullFrame();

 private:
  PP_Instance pp_instance_;
};

}  // namespace pp

#endif  // PPAPI_CPP_INSTANCE_H_
