import { Component, OnInit } from '@angular/core';
import { ArduinoService } from './arduino.service';

@Component({
  selector: 'app-arduino',
  templateUrl: './arduino.component.html',
  styleUrls: ['./arduino.component.css']
})
export class ArduinoComponent implements OnInit {
  error: any;
  success: string;

  constructor(private arduinoService: ArduinoService) {
  }

  ngOnInit() {
  }

  setName(newName: string) {
    this.arduinoService.setName(newName).subscribe(
      success => {
        this.success = 'Name updated';
      },
      error => {
        this.error = <any>error;
      }
    );
  }

  setInterval(newInterval: number) {
    this.arduinoService.setInterval(newInterval).subscribe(
      success => {
        this.success = 'Interval updated';
      },
      error => {
        this.error = <any>error;
      }
    );
  }
}
