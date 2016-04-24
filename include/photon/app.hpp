/*=================================================================================================
   Copyright (c) 2016 Joel de Guzman

   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.
   http://creativecommons.org/licenses/by-sa/4.0/
=================================================================================================*/
#if !defined(PHOTON_GUI_LIB_APP_APRIL_11_2016)
#define PHOTON_GUI_LIB_APP_APRIL_11_2016

#include <photon/support.hpp>
#include <photon/cursor.hpp>
#include <type_traits>
#include <vector>

namespace photon
{
   ////////////////////////////////////////////////////////////////////////////////////////////////
   // The Application
   ////////////////////////////////////////////////////////////////////////////////////////////////
   class app
   {
   public:
                           ~app();
                           app(app const&) = delete;
                           app& operator=(app const&) = delete;

      virtual void         key(key_info const& k);
      virtual void         run();
      cursor&              get_cursor(cursor::type t);

      double const         multi_click_speed = 0.5;
      double const         idle_time = 0.25;

   protected:
                           app();
   private:

      template <typename App, typename... Args>
      friend typename std::enable_if<
         std::is_base_of<App, app>::value, App&
      >::type
      make_app(Args const&... args);

      std::vector<cursor>  _cursors;
      double               _idle_time;
   };

   template <typename App, typename... Args>
   inline typename std::enable_if<
         std::is_base_of<App, app>::value, App&
      >::type
   make_app(Args const&... args)
   {
      extern app* app_ptr;
      static App app_obj{ args... };
      app_ptr = &app_obj;
      return app_obj;
   }
}

#endif