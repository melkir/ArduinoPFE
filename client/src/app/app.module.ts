import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';

import { AppComponent } from './app.component';
import { ArduinoComponent } from './arduino/arduino.component';
import { ArduinoService } from './arduino/arduino.service';

@NgModule({
  declarations: [
    AppComponent,
    ArduinoComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpModule
  ],
  providers: [
    ArduinoService
  ],
  bootstrap: [AppComponent]
})
export class AppModule {
}
