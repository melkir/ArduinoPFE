import { Injectable } from '@angular/core';
import { Http } from '@angular/http';
import { Observable } from 'rxjs/Observable';
import 'rxjs/add/operator/catch';
import 'rxjs/add/observable/throw';

@Injectable()
export class ArduinoService {
  private apiUrl = 'http://192.168.43.83/arduino/mode';

  constructor(private http: Http) {
  }

  getName(): Observable<string> {
    return this.http.get(this.apiUrl + '/read').catch(this.handleError);
  }

  setName(name: string) {
    return this.http.get(this.apiUrl + '/write/' + name).catch(this.handleError);
  }

  setInterval(interval: number) {
    return this.http.get(this.apiUrl + '/interval/' + interval).catch(this.handleError);
  }

  private handleError(err: Response | any) {
    console.log(err);
    return Observable.throw(err || 'Server error');
  }
}
