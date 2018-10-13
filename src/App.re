open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{"wrapper": style([flex(1.), paddingTop(Style.Pt(30.))])},
  );

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <View style=styles##wrapper> <Editor autoFocus=true /> </View>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));
