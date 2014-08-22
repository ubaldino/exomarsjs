App = Ember.Application.create();

App.Router.map( function() {
    this.route( "control" );
    this.route( "vision_artificial" );
});

/*
App.IndexRoute = Ember.Route.extend({
  model: function() {
    return ['red', 'yellow', 'blue'];
  }
});
*/