open Types;

let render = (ctx, state: alien) =>
  switch state.potentialSprite {
  | Some(img) =>
    HtmlImage.drawImage(img, int_of_float(state.x), int_of_float(state.y), ctx)
  | _ => ()
  };