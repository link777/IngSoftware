<?php
 
class Usuarios {
 
    /**
     * Make changes to the database.
     *
     * @return void
     */
    public function up()
    {
        
        Schema::create('usuario', function($tabla){
 
            $tabla->increments('id');
            $tabla->string('username', 60);
            $tabla->string('password', 100);
 
        });
 
        DB::table('usuario')->insert(
            array(
                'username' => 'admin',
                'password' => Hash::make('123456')
            )
        );
 
    }
 
    /**
     * Revert the changes to the database.
     *
     * @return void
     */
    public function down()
    {
        
        Schema::drop('usuario');
 
    }
 
}