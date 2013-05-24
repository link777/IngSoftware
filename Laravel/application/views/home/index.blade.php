@layout('layout')
 
@section('titulo')
 
    Home
 
@endsection
 
@section('mensaje')
 
    Bienvenido a la home!
 
@endsection
 
@section('contenido')
    <p>{{ HTML::link('home/logout', 'Logout') }}</p>    
 
<!--con Auth::user() podemos acceder a los campos del usuario en la tabla usuarios-->
Bienvenido {{ Auth::user()->username }}, tu password es {{ Auth::user()->password }} y tu id de usuario es {{ Auth::user()->id }}!
@endsection