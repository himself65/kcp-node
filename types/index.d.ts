export class KCP {
  constructor(conv: number)

  public setTimestamp(nodelay: number, interval: number, resend: number, nc: number): boolean

  public setWndSize(sndwnd: number, rcvwnd: number): boolean

  output: Function
}