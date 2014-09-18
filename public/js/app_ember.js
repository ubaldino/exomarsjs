App = Ember.Application.create();

App.Router.map( function() {
    this.route( "vision_artificial" );
    this.route( "tripulante" );
});

/*
App.IndexRoute = Ember.Route.extend({
  model: function() {
    return ['red', 'yellow', 'blue'];
  }
});
*/