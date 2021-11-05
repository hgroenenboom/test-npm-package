#include "napi.h"

Napi::ThreadSafeFunction threadsafeFunction;

Napi::Value length( const Napi::CallbackInfo& info )
{
    Napi::Env env = info.Env();

    if ( info.Length() < 1 )
    {
        Napi::TypeError::New( env, "Wrong number of arguments" ).ThrowAsJavaScriptException();
        return env.Null();
    }

    if ( !info[0].IsString() )
    {
        Napi::TypeError::New( env, "Wrong arguments" ).ThrowAsJavaScriptException();
        return env.Null();
    }

    const std::string string = info[0].As<Napi::String>();
    const auto size = string.size();

    if( threadsafeFunction )
    {
        auto callback = [size]( Napi::Env env, Napi::Function jsCallback, void* ) 
        {
            if ( env != nullptr )
            {
                jsCallback.Call( { Napi::Number::New( env, size ) } );
            }
        };

        threadsafeFunction.BlockingCall( (void*) nullptr, callback );
    }
    
    return Napi::Number::New(env, size);
}

Napi::Value registerLengthCallback( const Napi::CallbackInfo& info )
{
    Napi::Env env = info.Env();

    if ( info.Length() < 1 || !info[0].IsFunction() )
    {
        Napi::TypeError::New( env, "Wrong arguments supplied, expects a single lambda function" )
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    threadsafeFunction =
        Napi::ThreadSafeFunction::New( env,                          // Environment
                                       info[0].As<Napi::Function>(), // JS function from caller
                                       "ThreadsafeFunction",         // Resource name
                                       0,                            // Max queue size (0 = unlimited).
                                       1                             // Initial thread count
        );

    return env.Null();
}

Napi::Object Init( Napi::Env env, Napi::Object exports )
{
    exports["length"]                  = Napi::Function::New( env, length );
    exports["registerLengthCallback"]  = Napi::Function::New( env, registerLengthCallback );

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
