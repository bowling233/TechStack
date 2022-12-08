# React Basic

> Contents are from [Tutorial: Intro to React](https://reactjs.org/tutorial/tutorial.html#setup-option-2-local-development-environment)

[TOC]

## Setup

* Install `Node.js`

* run the command, this will create a folder `my-app` under your working directory:

  ```bash
  npx create-react-app my-app
  ```

* Inside the folder, you can run `npm start` to view the compiled website.

## Overview

* React is a declarative, efficient, and flexible **JavaScript library for building user interfaces**. It lets you compose complex UIs from small and isolated pieces of code called “**components**”.

* We use **components** to tell React what we want to see on the screen. When our data changes, React will efficiently update and re-render our components.

  * A component takes in parameters, called `props` (short for “properties”), and returns a hierarchy of views to display via the `render` method.

  * The `render` method returns a *description* of what you want to see on the screen. React takes the description and displays the result. In particular, `render` returns a **React element**, which is a lightweight description of what to render. Most React developers use a special syntax called “JSX” which makes these structures easier to write. The `<div />` syntax is transformed at build time to `React.createElement('div')`

    * You can put *any* JavaScript expressions within braces inside JSX.

      > **NOTE: WITHIN BRACES**
      >
      > Remember what we've learnt in MIT Web Crush Course:
      >
      > * `()` to write HTML inside JavaScript
      > * `{}` to come back to JavaScript

    * Each React element is a JavaScript object that you can store in a variable or pass around in your program.

* Example

  ```react
  class ShoppingList extends React.Component {
    render() {
      return (
        <div className="shopping-list">
          <h1>Shopping List for {this.props.name}</h1>
          <ul>
            <li>Instagram</li>
            <li>WhatsApp</li>
            <li>Oculus</li>
          </ul>
        </div>
      );
    }
  }
  
  // Example usage: <ShoppingList name="Mark" />
  // The example above is equivalent to:
  return React.createElement('div', {className: 'shopping-list'},
    React.createElement('h1', /* ... h1 children ... */),
    React.createElement('ul', /* ... ul children ... */)
  );
  ```

## Props and States

### Passing Data Through Props

```react
class Board extends React.Component {
  renderSquare(i) {
    return <Square value={i} />;//NOTE HERE
  }
}

class Square extends React.Component {
  render() {
    return (
      <button className="square">
        {this.props.value}//NOTE HERE
      </button>
    );
  }
}
```

* Also you can pass functions with `props={()=> function()}` to pass `function` as the `props` prop.

  > **NOTICE**
  >
  > Do not write `props={function()}`. [Here](https://yehudakatz.com/2011/08/11/understanding-javascript-function-invocation-and-this/) is the reason.

### Use state

* React components can have state by setting `this.state` in their **constructors**.
* `this.state` should be considered as private to a React component that it’s defined in.
* By calling `this.setState` from an `onClick` handler in the Square’s `render` method, we tell React to **re-render that Square** whenever its `<button>` is clicked.

```react
class Square extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      value: null,
    };
 }
  render() {
    return (
      <button
        className="square"
        onClick={() => this.setState({value: 'X'})}
      >
        {this.state.value}
      </button>
    );
  }
}
```

> **Note**
>
> In [JavaScript classes](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes), you need to always call `super` when defining the constructor of a subclass. All React component classes that have a `constructor` should start with a `super(props)` call.
>
> A bit like the C++ classes, uh-huh?

### Lifting State Up

* To collect data from **multiple children**, or to have two child components **communicate with each other**, you need to declare the **shared state** in their parent component instead. The parent component can pass the state back down to the children by using props; this keeps the child components in sync with each other and with the parent component.

The Board's method will be changed to:

```react
renderSquare(i) {
  return <Square value={this.state.squares[i]} />;//pass state as props
}
```

> REMEMBER state is considered to be **private to a component that defines it**, we cannot update the Board’s state directly from Square.

* Instead, we’ll **pass down a function** from the Board to the Square, and we’ll have Square call that function when a square is clicked. 

```react
class Square extends React.Component {//...
      <button
        className="square"
        onClick={() => this.props.onClick()}>//NOTICE how props function is used
      //...
}

class Board extends React.Component {
    //...
  handleClick(i) {
    const squares = this.state.squares.slice();//**NOTICE**
    squares[i] = 'X';
    this.setState({squares: squares});
  } 
  renderSquare(i) {
    return (
      <Square
        value={this.state.squares[i]}
        onClick={() => this.handleClick(i)}/>//NOTICE
    );
  }
  //...
}  
```

> When a Square is clicked, the `onClick` function provided by the Board is called. Here’s a review of how this is achieved:
>
> 1. The `onClick` prop on the built-in DOM `<button>` component tells React to set up a click event listener.
> 2. When the button is clicked, React will call the `onClick` event handler that is defined in Square’s `render()` method.
> 3. This event handler calls `this.props.onClick()`. The Square’s `onClick` prop was specified by the Board.
> 4. Since the Board passed `onClick={() => this.handleClick(i)}` to Square, the Square calls the Board’s `handleClick(i)` when clicked.
> 5. We have not defined the `handleClick()` method yet, so our code crashes. If you click a square now, you should see a red error screen saying something like “this.handleClick is not a function”.
>
> > Note
> >
> > The DOM `<button>` element’s `onClick` attribute has a special meaning to React because it is a built-in component. For custom components like Square, the naming is up to you. We could give any name to the Square’s `onClick` prop or Board’s `handleClick` method, and the code would work the same. In React, it’s conventional to use `on[Event]` names for props which represent events and `handle[Event]` for the methods which handle the events.

### Immutability Is Important

There are generally **two approaches to changing data**. The first approach is to *mutate* the data by directly changing the data’s values. The second approach is to replace the data with a new copy which has the desired changes.

* Data Change with Mutation

```
var player = {score: 1, name: 'Jeff'};
player.score = 2;
// Now player is {score: 2, name: 'Jeff'}
```

* Data Change without Mutation

```
var player = {score: 1, name: 'Jeff'};

var newPlayer = Object.assign({}, player, {score: 2});
// Now player is unchanged, but newPlayer is {score: 2, name: 'Jeff'}

// Or if you are using object spread syntax, you can write:
// var newPlayer = {...player, score: 2};
```

The end result is the same but by not mutating (or changing the underlying data) directly, we gain several benefits described below.

* Complex Features Become Simple

Immutability makes complex features much easier to implement. Later in this tutorial, we will implement a “time travel” feature that allows us to review the tic-tac-toe game’s history and “jump back” to previous moves. This functionality isn’t specific to games — an ability to **undo and redo certain actions** is a common requirement in applications. Avoiding direct data mutation lets us **keep previous versions** of the game’s history intact, and reuse them later.

* Detecting Changes

Detecting changes in mutable objects is difficult because they are modified directly. This detection requires the mutable object to be compared to previous copies of itself and the entire object tree to be traversed.

Detecting changes in immutable objects is considerably easier. If the immutable object that is being referenced is different than the previous one, then the object has changed.

* Determining When to Re-Render in React

The main benefit of immutability is that it helps you build *pure components* in React. Immutable data can **easily determine if changes have been made**, which helps to determine when a component requires re-rendering.

You can learn more about `shouldComponentUpdate()` and how you can build *pure components* by reading [Optimizing Performance](https://reactjs.org/docs/optimizing-performance.html#examples).

### Function Components

* **function components** are a simpler way to write components that only contain a `render` method and don’t have their own state.
* Instead of defining a class which extends `React.Component`, we can write a function that takes `props` as input and returns what should be rendered.
* Function components are **less tedious to write** than classes, and many components can be expressed this way.

```react
function Square(props) {
  return (
    <button className="square" onClick={props.onClick}>
      {props.value}
    </button>
  );
}
```

> NOTE:
>
> * `this.props` changed to `props`
>
> * also changed `onClick={() => this.props.onClick()}` to a shorter `onClick={props.onClick}` (note the lack of parentheses on *both* sides).

