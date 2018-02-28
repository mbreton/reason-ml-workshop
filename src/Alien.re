open Types;

let moveAlien = (elapsedTime: float, a: alien) : alien => {
  let x = a.x +. elapsedTime *. 0.3 *. float_of_int(a.direction);
  switch (x > 0., x < 600.) {
  | (true, true) => {...a, x}
  | (false, true) => {
      ...a,
      x: 0.,
      y: a.y +. 40.,
      direction: a.direction * (-1)
    }
  | (true, false) => {
      ...a,
      x: 600. -. a.height,
      y: a.y +. 40.,
      direction: a.direction * (-1)
    }
  | _ => failwith("Impossible case ...")
  };
};

let moveAliens = (aliens: list(alien), elapsedTime: float) : list(alien) =>
  aliens
  |> List.map(moveAlien(elapsedTime))
  |> List.filter((a: alien) => a.y < 400.);

let reducer = (state: alienState, action: Actions.all) : alienState => {
  let now = Js.Date.now();
  switch action {
  | AlienImageLoaded(img) => {
      ...state,
      itemModel: {
        ...state.itemModel,
        potentialSprite: Some(img)
      }
    }
  | ResetInGame => {...state, lastSpawn: now}
  | Tick(elapsedTime) =>
    let hasToRespawn = now -. state.lastSpawn > 600.;
    let aliens =
      moveAliens(
        hasToRespawn ? state.aliens @ [state.itemModel] : state.aliens,
        elapsedTime
      );
    {...state, lastSpawn: hasToRespawn ? now : state.lastSpawn, aliens};
  | _ => state
  };
};

let render = (ctx, state: alien) =>
  switch state.potentialSprite {
  | Some(img) =>
    HtmlImage.drawImage(img, int_of_float(state.x), int_of_float(state.y), ctx)
  | _ => ()
  };