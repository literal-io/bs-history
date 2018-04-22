module Location = {
  type t;
  [@bs.get] external pathname : t => string = "";
  [@bs.get] external search : t => string = "";
  [@bs.get] external hash : t => string = "";
};

module Action = {
  [@bs.deriving jsConverter]
  type t = [
    | [@bs.as "PUSH"] `Push
    | [@bs.as "POP"] `Pop
    | [@bs.as "REPLACE"] `Replace
  ];
};

type t;

[@bs.get] external location : t => Location.t = "";

[@bs.send.pipe : t]
external listen :
  ([@bs] ((Location.t, string) => unit)) => [@bs] (unit => unit) =
  "";

let listen = (cb) =>
  listen((. location, action) =>
    cb(
      location, 
      action
      |> Action.tFromJs
      |> Js.Option.getExn
    )
  );

[@bs.send.pipe : t] external replace : string => unit = "";

[@bs.send.pipe : t] external push : string => unit = "";

type memoryHistoryOptions = {
  .
  "initialEntries": array(string),
  "initialIndex": int,
  "keyLength": int
};

[@bs.obj]
external makeMemoryHistoryOptions :
  (~initialEntries: array(string), ~initialIndex: int, ~keyLength: int) =>
  memoryHistoryOptions =
  "";

[@bs.module "history/createMemoryHistory"]
external createMemoryHistory : memoryHistoryOptions => t = "default";

type hashHistoryOptions = {. "basename": string};

[@bs.obj]
external makeHashHistoryOptions : (~basename: string) => hashHistoryOptions =
  "";

[@bs.module "history/createHashHistory"]
external createHashHistory : hashHistoryOptions => t = "default";