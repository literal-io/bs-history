module Location = {
  type t;
  [@bs.get] external pathname : t => string = "";
  [@bs.get] external search : t => string = "";
  [@bs.get] external hash : t => string = "";
};

module Action = {
  type t;
};

type t;

[@bs.get] external location : t => Location.t = "";

[@bs.send.pipe : t]
external listen :
  ([@bs] ((Location.t, Action.t) => unit)) => [@bs] (unit => unit) =
  "";

[@bs.send.pipe : t] external replace : string => unit = "";

[@bs.send.pipe : t] external push : string => unit = "";

type memoryHistoryOptions = {
  .
  "initialEntries": array(string),
  "initialIndex": int,
  "keyLength": int
};

[@bs.obj]
external makeMemoryHistory :
  (~initialEntries: array(string), ~initialIndex: int, ~keyLength: int) =>
  memoryHistoryOptions =
  "";

[@bs.module "history/createMemoryHistory"]
external createMemoryHistory : memoryHistoryOptions => t = "default";