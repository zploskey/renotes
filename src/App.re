open BsReactNative;

let styles =
  StyleSheet.create(
    Style.{"wrapper": style([flex(1.), paddingTop(Style.Pt(30.))])},
  );

type action =
  | ChangeNote(Note.t)
  | NewNote
  | ViewNote(int)
  | ViewNoteList;

type state = {
  notes: array(Note.t),
  currentNoteIndex: option(int),
};

let renderNoteListItem = (~send) =>
  FlatList.renderItem((note: FlatList.renderBag(Note.t)) =>
    <View>
      <Text onPress={() => send(ViewNote(note.index))}>
        {ReasonReact.string(note.item.title)}
      </Text>
    </View>
  );

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {notes: [|Note.empty()|], currentNoteIndex: Some(0)},
  reducer: (action, state) =>
    switch (action) {
    | NewNote =>
      let notes = Belt.Array.concat([|Note.empty()|], state.notes);
      ReasonReact.Update({notes, currentNoteIndex: Some(0)});
    | ChangeNote(note) =>
      switch (state.currentNoteIndex) {
      | Some(i) =>
        state.notes[i] = note;
        ReasonReact.Update({...state, notes: state.notes});
      | None => ReasonReact.NoUpdate
      }
    | ViewNote(i) =>
      ReasonReact.Update({...state, currentNoteIndex: Some(i)})
    | ViewNoteList => ReasonReact.Update({...state, currentNoteIndex: None})
    },
  render: ({state, send}) =>
    <View style=styles##wrapper>
      {
        let notes = state.notes;
        switch (state.currentNoteIndex) {
        | Some(i) =>
          let note = notes[i];
          <Editor
            note
            onBack=(() => send(ViewNoteList))
            onNoteChanged=(note => send(ChangeNote(note)))
            autoFocus=true
          />;
        | None =>
          <View>
            <Button title="New Note" onPress=(() => send(NewNote)) />
            <FlatList
              data={state.notes}
              keyExtractor=(
                (note, i) => string_of_int(i) ++ "-" ++ note.title
              )
              renderItem={renderNoteListItem(~send)}
            />
          </View>
        };
      }
    </View>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));
