module TestAlloca

open FStar.HyperStack.ST

let size (): St (x: UInt32.t{ UInt32.v x == 42}) =
  42ul

let main (): St Int32.t =
  push_frame ();
  let s = size () in
  let b = Buffer.create 0l s in
  let r = Buffer.index b 41ul in
  pop_frame ();
  r
