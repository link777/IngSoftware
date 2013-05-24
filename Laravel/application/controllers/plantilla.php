<?php
class Plantilla_Controller extends Base_Controller
{
 
    public function action_index()
    {
 
        return View::make('plantilla');
 
    }
 
	public function action_login()
	{
	 
		$datos = array(array('titulo' => 'nuevo'), array('titulo' => 'otro más'));
		return View::make('login')->with('posts', $datos);
	 
	}
 
}