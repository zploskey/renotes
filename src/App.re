open BsReactNative;

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <View>
      <Text> {ReasonReact.string({|

Hello Word!
    |})} </Text>
    </View>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));
