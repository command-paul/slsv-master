%module(directors="1") eventHandlers
%{
    #include "eventHandlers.hpp"
%}

%feature("director") Callback;

// Source of eventHandler